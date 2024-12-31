#include "parallel_for.h"

#if defined(__APPLE__) || defined(__linux__)
#define POSIX
#elif defined(_WIN32)

#else
#error "Platform not supported."
#endif

#include <stdio.h>
#include <stdlib.h>

#ifdef POSIX
#include <pthread.h>
#include <unistd.h>
#else
#include <windows.h>
#endif

/******************************************************************************
* A task descriptor specifying the input element and the address at which the *
* output element should be stored.                                            *
******************************************************************************/
typedef struct task_descriptor {
    void* input_element;
    void** output_element_address;
} task_descriptor;

/************************************************************
* This structure implements a concurrent array-based queue. *
************************************************************/
typedef struct concurrent_queue {

#ifdef POSIX
    pthread_mutex_t mutex;
#elif defined(_WIN32)
    CRITICAL_SECTION criticalSection;
#endif

    task_descriptor** array;
    size_t begin_index;
    size_t end_index;
    size_t size;
    size_t len;
} concurrent_queue;

/************************************************************
* Initializes the input concurrent queue to an empty state. *
************************************************************/
static int concurrent_queue_init(concurrent_queue* queue, size_t len)
{
    int ret;
    queue->array = malloc(len * sizeof(*queue->array));

    if (queue->array == NULL)
    {
        return ERROR_FORP_MALLOC_FAIL;
    }

    queue->begin_index = 0;
    queue->end_index = 0;
    queue->size = 0;
    queue->len = len;

#ifdef POSIX

    ret = pthread_mutex_init(&queue->mutex, NULL);

    if (ret != 0)
    {
        return ERROR_FORP_NO_MUTEX_INIT;
    }

#else

    InitializeCriticalSection(&queue->criticalSection);

#endif

    return ERROR_FORP_SUCCESS;
}

/******************************************************
* Appends a task descriptor to the tail of the queue. *
******************************************************/
static void concurrent_queue_enqueue(concurrent_queue* queue,
    task_descriptor* descriptor)
{
    queue->array[queue->end_index] = descriptor;
    queue->end_index++;
    queue->size++;
}

/******************************************************************************
* Removes the head element from the queue. Unlike all other functions related *
* to the queue, this is one is thread-safe.                                   *
******************************************************************************/
static task_descriptor* concurrent_queue_dequeue(concurrent_queue* queue)
{
    task_descriptor* descriptor;

#ifdef POSIX
    pthread_mutex_lock(&queue->mutex);
#else
    EnterCriticalSection(&queue->criticalSection);
#endif

    if (queue->size > 0)
    {
        descriptor = queue->array[queue->begin_index];
        queue->begin_index++;
        queue->size--;
    }
    else
    {
        descriptor = NULL;
    }

#ifdef POSIX
    pthread_mutex_unlock(&queue->mutex);
#else
    LeaveCriticalSection(&queue->criticalSection);
#endif

    return descriptor;
}

/*****************************************************************************
* Releases all the resources occupied by the queue, or namely, the mutex and *
* the array.                                                                 *
*****************************************************************************/
static int concurrent_queue_destroy(concurrent_queue* queue)
{
    int ret;
    size_t i;

    for (i = 0; i < queue->len; i++)
    {
        free(queue->array[i]);
    }

    free(queue->array);

#ifdef POSIX
    ret = pthread_mutex_destroy(&queue->mutex);
    return ret == 0 ? ERROR_FORP_SUCCESS : ERROR_FORP_NO_MUTEX_DESTROY;
#else
    DeleteCriticalSection(&queue->criticalSection);
    return ERROR_FORP_SUCCESS;
#endif

}

/*******************************************************
* Returns the number of processors on Mac OS or Linux. *
*******************************************************/
static int get_number_of_processors_apple_linux(size_t* p_number_of_processors)
{
#ifdef POSIX
    * p_number_of_processors = (size_t)sysconf(_SC_NPROCESSORS_ONLN);
#endif

    return ERROR_FORP_SUCCESS;
}

/***********************************************
* Returns the number of processors on Windows. *
***********************************************/
static int get_number_of_processors_windows(size_t* p_number_of_processors)
{
#ifdef _WIN32
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    *p_number_of_processors = (size_t)2 * si.dwNumberOfProcessors;
#endif

    return ERROR_FORP_SUCCESS;
}

/**************************************************************
* A portable function for returning the number of processors. *
**************************************************************/
static int get_number_of_processors(size_t* p_number_of_processors)
{
#ifdef POSIX
    return get_number_of_processors_apple_linux(p_number_of_processors);
#else
    return get_number_of_processors_windows(p_number_of_processors);
#endif
}

/*****************************************************************************
* Specifies the worker thread arguments. Holds the queue and the function to *
* be applied to each queue element.                                          *
*****************************************************************************/
typedef struct worker_thread_proc_args {
    concurrent_queue* queue;
    void* (*func)(void*);
    int return_status;
} worker_thread_proc_args;

/*********************************
* Implements the worker threads. *
*********************************/
static void* worker_thread_proc(void* args)
{
    worker_thread_proc_args* worker_thread_proc_arguments =
        (worker_thread_proc_args*)args;

    concurrent_queue* queue = worker_thread_proc_arguments->queue;
    void* (*func)(void*) = worker_thread_proc_arguments->func;
    task_descriptor* task_desc;
    int ret = 0;

#ifdef POSIX
    ret = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
#endif

    if (ret != 0)
    {
        worker_thread_proc_arguments->return_status = ret;
        return NULL;
    }
    else
    {
        worker_thread_proc_arguments->return_status = 0;
    }

    while ((task_desc = concurrent_queue_dequeue(queue)) != NULL)
    {
        *task_desc->output_element_address = func(task_desc->input_element);
    }

    return NULL;
}

/***************************************
* Cancels all the first 'len' threads. *
***************************************/
#ifdef POSIX
static void cancel_threads(pthread_t* pthreads, size_t len)
#else
static void cancel_threads(HANDLE* threads, size_t len)
#endif
{
    size_t i;

    for (i = 0; i < len; ++i)
    {

#ifdef POSIX
        pthread_cancel(pthreads[i]);
#else
        TerminateThread(threads[i], 0);
#endif

    }
}

/***********************************************************
* The actual implementation of the parallel for construct. *
***********************************************************/
int forp(void** input, void** output, size_t len, void* (*func)(void*))
{
    size_t number_of_cores;
    size_t szi;
    int ret;
    int join_ret = ERROR_FORP_SUCCESS;
    concurrent_queue queue;
    task_descriptor* task_desc;
    worker_thread_proc_args* wtpa;

#ifdef POSIX

    pthread_t* threads;

#else

    HANDLE* threads;

#endif

    if (input == NULL || output == NULL || func == NULL)
    {
        return ERROR_FORP_NO_ARGS;
    }

    if (len == 0)
    {
        /*****************
        * Nothing to do. *
        *****************/
        return ERROR_FORP_SUCCESS;
    }

    ret = get_number_of_processors(&number_of_cores);

    if (ret != ERROR_FORP_SUCCESS)
    {
        return ret;
    }

    if (number_of_cores == 0)
    {
        return ERROR_FORP_UNKNOWN_CORES;
    }

    if ((ret = concurrent_queue_init(&queue, len)) != ERROR_FORP_SUCCESS)
    {
        return ret;
    }

    /**************************************
    * Create a concurrent queue of tasks. *
    **************************************/
    for (szi = 0; szi < len; szi++)
    {
        task_desc = malloc(sizeof * task_desc);

        if (task_desc == NULL)
        {
            concurrent_queue_destroy(&queue);
            return ERROR_FORP_MALLOC_FAIL;
        }

        task_desc->input_element = input[szi];
        task_desc->output_element_address = &output[szi];
        concurrent_queue_enqueue(&queue, task_desc);

        if (ret != ERROR_FORP_SUCCESS)
        {
            concurrent_queue_destroy(&queue);
            return ret;
        }
    }

    /*****************************
    * Create the worker threads. *
    *****************************/
    threads = malloc(number_of_cores * sizeof(*threads));

    if (threads == NULL)
    {
        concurrent_queue_destroy(&queue);
        return ERROR_FORP_MALLOC_FAIL;
    }

    wtpa = malloc(number_of_cores * sizeof(*wtpa));

    if (wtpa == NULL)
    {
        free(threads);
        concurrent_queue_destroy(&queue);
        return ERROR_FORP_MALLOC_FAIL;
    }

    for (szi = 0; szi < number_of_cores; szi++)
    {
        wtpa[szi].queue = &queue;
        wtpa[szi].func = func;
        wtpa[szi].return_status = 0;

#ifdef POSIX
        ret = pthread_create(&threads[szi],
            NULL,
            worker_thread_proc,
            &wtpa[szi]);
#else
        threads[szi] = CreateThread(NULL,
            100000,
            (LPTHREAD_START_ROUTINE)worker_thread_proc,
            (LPVOID)&wtpa[szi],
            0,
            NULL);
#endif

        if (ret != 0)
        {
            cancel_threads(threads, szi);
            concurrent_queue_destroy(&queue);
            return ERROR_FORP_NO_THREAD;
        }

        if (wtpa[szi].return_status != 0)
        {
            cancel_threads(threads, szi + 1);
            concurrent_queue_destroy(&queue);
            return ERROR_FORP_NO_SETCANCELTYPE;
        }
    }

    /***********************************************
    * Wait for all the worker threads to complete. *
    ***********************************************/
    for (szi = 0; szi < number_of_cores; szi++)
    {
#ifdef _WIN32

        if (WaitForSingleObject(threads[szi], INFINITE) != 0 && join_ret == 0)
        {
            join_ret = ERROR_FORP_NO_JOIN;
        }
#else
        join_ret = pthread_join(threads[szi], NULL);

        if (ret != 0 && join_ret == ERROR_FORP_SUCCESS)
        {
            join_ret = ERROR_FORP_NO_JOIN;
        }
#endif
    }

    return join_ret;
}

const char* forp_error(int error_code)
{
    switch (error_code)
    {
    case ERROR_FORP_SUCCESS:
        return "forp succeeded.";

    case ERROR_FORP_NO_ARGS:
        return "Some arguments missing.";

    case ERROR_FORP_NO_JOIN:
        return "Could not join a thread.";

    case ERROR_FORP_CPU_FEOF:
        return "Reached EOF while reading the number of processors.";

    case ERROR_FORP_NO_THREAD:
        return "Could create a thread.";

    case ERROR_FORP_CPU_FERROR:
        return "An error occured while reading the number of processors.";

    case ERROR_FORP_POPEN_FAIL:
        return "Could not execute a program in popen.";

    case ERROR_FORP_MALLOC_FAIL:
        return "A call to malloc returned NULL.";

    case ERROR_FORP_SSCANF_FAIL:
        return "sscanf failed.";

    case ERROR_FORP_NO_MUTEX_INIT:
        return "Could not initialize a mutex.";

    case ERROR_FORP_NO_MUTEX_DESTROY:
        return "Could not destroy a mutex.";

    case ERROR_FORP_UNKNOWN_CORES:
        return "Could not determine the number of processors.";

    case ERROR_FORP_NO_SETCANCELTYPE:
        return "setcanceltype failed.";

    default:
        return "Unknown error code.";
    }
}