/**
 * @file    addition.c
 * @brief   Sum of array with multiple threads
 *
 * @author  Rohit Nimkar
 * @date    06/10/2023
 * @version 1.0
 */

#include <bits/types/struct_timeval.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

typedef struct input
{
    int *pArr;
    size_t start_index;
    size_t nElements;
} thread_input_t;

void * addition(void *pArgs)
{
    thread_input_t *pInput = (thread_input_t *)pArgs;
    size_t sum = 0;
    for(size_t idx = 0; idx < pInput->nElements; ++idx)
    {
        sum += *(pInput->pArr + idx + pInput->start_index);
    }
    return (void *) sum;
}

int *build_arr(size_t size)
{
    int *pArr = (int *)calloc(size, sizeof(int));
    if(NULL != pArr)
    {
        for(size_t idx = 0; idx < size; ++idx)
        {
            *(pArr + idx) = idx;
        }
    }
    return (pArr);
}

int main()
{
    thread_input_t *pThreadInput = NULL;
    pthread_t *pHndl;
    size_t total_threads;
    int nThreads = 4;
    size_t nElementsPerThread = 25000;
    size_t totalElements = 100000;
    int *pArr = NULL;
    void *threadRet = NULL;
    size_t sumFinal = 0;
    struct timeval initial_tv = {0};
    struct timeval final_tv = {0};
    int ret = 0;

    printf("Enter number of threads: ");
    scanf("%d", &nThreads);

    do
    {
        printf("Enter total number of elements (multiple of %d): ", nThreads);
        scanf("%zu", &totalElements);
    }while (totalElements % nThreads);

    nElementsPerThread = totalElements/nThreads;

    pArr = build_arr(totalElements);
    if(NULL == pArr)
    {
        perror("failed to allocate array");
        _exit(errno);
    }

    /* generate array */
    pArr = build_arr(totalElements);

    if(nThreads == 1)
    {
        gettimeofday(&initial_tv, NULL);
        printf("Running in single threaded mode\n");
        thread_input_t singleInput = {};
        singleInput.pArr = pArr;
        singleInput.nElements = totalElements;
        singleInput.start_index = 0;
        sumFinal = (unsigned long) addition(&singleInput);
        gettimeofday(&final_tv, NULL);
    }
    else
    {
        printf("Running in multi-threaded mode\n");
        // generate threadHandles
        pHndl = (pthread_t *)calloc(nThreads, sizeof(pthread_t));
        if(NULL == pHndl)
        {
            free(pArr);
            perror("failed to allocate thread handles");
            _exit(errno);
        }

        // allocate thread pInputs
        pThreadInput = (thread_input_t *)calloc(nThreads, sizeof(thread_input_t));
        if(NULL == pThreadInput)
        {
            free(pHndl);
            free(pArr);
            perror("failed to allocate thread pInputs");
            _exit(errno);
        }
        ret = gettimeofday(&initial_tv, NULL); 

        // create pInputs;
        for (size_t idx = 0; idx < nThreads; idx++)
        {
            (pThreadInput + idx)->pArr = pArr;
            (pThreadInput + idx)->start_index = nElementsPerThread * idx;
            (pThreadInput + idx)->nElements = nElementsPerThread;

            ret = pthread_create(pHndl + idx, NULL, addition, (void *)(pThreadInput + idx));
            if(0 > ret)
            {
                perror("failed to create threads");
                break;
            }
        }

        /* join all threads */
        for(size_t idx = 0; idx < nThreads; ++idx)
        {
            /* verify if thread created */
            if(0 != *(pHndl + idx))
            {
                ret = pthread_join(*(pHndl + idx), &threadRet);
                if( 0 > ret)
                {
                    perror("pthread_join failed");
                    /* handle this case gracefully */
                    continue;
                }

                sumFinal += (size_t) threadRet;
            }
        }
        ret = gettimeofday(&final_tv, NULL);
        free(pThreadInput);
        free(pHndl);
    }

    printf("Final sum: %lu\n", sumFinal);
    // printf("Initial time %ld %ld\n", initial_tv.tv_sec, initial_tv.tv_usec);
    // printf("Initial time %ld %ld\n", final_tv.tv_sec, final_tv.tv_usec);

    struct timeval diff = {};
    /* calculate difference final - initial */
    if(final_tv.tv_usec < initial_tv.tv_usec)
    {
        diff.tv_usec = 1000000 + final_tv.tv_usec - initial_tv.tv_usec;
        diff.tv_sec = final_tv.tv_sec - initial_tv.tv_sec - 1;
    }
    else
    {
        diff.tv_usec = final_tv.tv_usec - initial_tv.tv_usec;
        diff.tv_sec = final_tv.tv_sec - initial_tv.tv_sec;
    }
    printf("Total time taken: %lu seconds %lu useconds\n", diff.tv_sec, diff.tv_usec);

    /* release resources */
    free(pArr);

    return (0);
}
