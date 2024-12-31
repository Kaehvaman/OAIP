#ifndef PARALLEL_FOR_H
#define PARALLEL_FOR_H

#include <stdlib.h>

#define ERROR_FORP_SUCCESS 0
#define ERROR_FORP_NO_ARGS 1
#define ERROR_FORP_UNKNOWN_CORES 2
#define ERROR_FORP_NO_MUTEX_INIT 3
#define ERROR_FORP_NO_MUTEX_DESTROY 4
#define ERROR_FORP_MALLOC_FAIL 5
#define ERROR_FORP_SSCANF_FAIL 6
#define ERROR_FORP_POPEN_FAIL 7
#define ERROR_FORP_CPU_FEOF 8
#define ERROR_FORP_CPU_FERROR 9
#define ERROR_FORP_NO_THREAD 10
#define ERROR_FORP_NO_SETCANCELTYPE 11
#define ERROR_FORP_NO_JOIN 12

/*******************************************************************************
* Runs a multithreaded for loop over the input array producing the results and *
* storing them in the output array.                                            *
*******************************************************************************/
int forp(void** input,
    void** output,
    size_t len,
    void* (*func)(void*));

/*************************************************************************
* Returns a human-readable description of an error code related to forp. *
*************************************************************************/
const char* forp_error(int error_code);

#endif /* PARALLEL_FOR_H */