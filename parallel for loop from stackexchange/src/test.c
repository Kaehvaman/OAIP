#include "parallel_for.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined(__APPLE__) || defined(__linux__)
#define POSIX
#endif

#if defined(POSIX)
#include <sys/time.h>
#elif defined(_WIN32)
#include <windows.h>
#else
#error "Platform not supported."
#endif

/*********************************
* Implements a dummy heavy task. *
*********************************/
static unsigned long long fibonacci(unsigned long long num)
{
    switch (num)
    {
    case 0:
        return 0;

    case 1:
        return 1;

    default:
        return fibonacci(num - 1) + fibonacci(num - 2);
    }
}

/*******************************
* The worker thread procedure. *
*******************************/
static void* fibonacci_func(void* arg)
{
    unsigned long long* pa = (unsigned long long*) arg;
    unsigned long long* result = malloc(sizeof(*result));
    *result = fibonacci(*pa);
    return result;
}

/**************************************
* Populates randomly the input array. *
**************************************/
static void populate_input_randomly(void** input_array, size_t len)
{
    unsigned long long* input_datum;
    size_t i;

    for (i = 0; i < len; i++)
    {
        input_datum = malloc(sizeof(unsigned long long));
        *input_datum = 20 + rand() % 21;
        input_array[i] = input_datum;
    }
}

/***************************
* Prints the output array. *
***************************/
static void print_output(void** output, size_t len)
{
    void* raw_datum;
    unsigned long long datum;
    size_t i;
    char* separator = "";
    printf("[");

    for (i = 0; i < len; i++) {
        printf("%s", separator);
        separator = ", ";
        raw_datum = output[i];
        datum = *((unsigned long long*) raw_datum);
        printf("%llu", datum);
    }

    puts("]");
}

/**************************************************************
* Returns a current millisecond count. Used for benchmarking. *
**************************************************************/
static unsigned long long get_milliseconds()
{
#ifdef POSIX
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 1000 * tv.tv_sec + tv.tv_usec / 1000;
#else
    return (unsigned long long) GetTickCount64();
#endif
}

#define N 100

int main(int argc, const char* argv[]) {
    void* input[N];
    void* output[N];
    unsigned long long start;
    unsigned long long end;
    size_t i;
    int error_code;

    srand((unsigned int)time(NULL));
    populate_input_randomly(input, N);

    start = get_milliseconds();
    error_code = forp(input, output, N, fibonacci_func);
    end = get_milliseconds();

    print_output(output, N);
    printf("Parallel for took %llu milliseconds. Error message: %s\n\n",
        end - start,
        forp_error(error_code));

    start = get_milliseconds();

    for (i = 0; i < N; i++)
    {
        output[i] = fibonacci_func(input[i]);
    }

    end = get_milliseconds();
    print_output(output, N);
    printf("Sequential for took %llu milliseconds.\n", end - start);

#ifdef _WIN32
    getchar();
#endif

    return 0;
}