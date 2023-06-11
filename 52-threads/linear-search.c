/**
 * @file    linear-search.c
 * @brief   Linear search with multiple threads
 *
 * @author  Rohit Nimkar
 * @date    06/11/2023
 * @version 1.0
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

typedef struct input
{
    int *pArr;
    size_t start_index;
    size_t nElements;
    int key;
} thread_input_t;

void *search(void *pArgs)
{
    thread_input_t *pInput = (thread_input_t *)pArgs;
    for(size_t idx = pInput->start_index; idx < pInput->nElements + pInput->start_index; ++idx)
    {
            // printf("[%lu] searching %d against %d\n",pthread_self(), pInput->key, *(pInput->pArr + idx));
        if(pInput->key == *(pInput->pArr + idx))
        {
            return (void *)idx;
        }
    }
    return NULL;
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

void printArr(int *pArr, size_t len)
{
    for (size_t idx = 0; idx < len; ++idx)
    {
        printf("%3d", *(pArr + idx));
    }
    putchar('\n');
}

int main()
{
    thread_input_t *pThreadInput = NULL;
    pthread_t *pHndl;
    size_t total_threads;
    size_t nThreads = 4;
    size_t nElementsPerThread = 5;
    size_t totalElements = 20;
    int *pArr = NULL;
    void *threadRet = NULL;
    size_t key = 15;
    
    int ret = 0;
    pArr = build_arr(totalElements);
    if(NULL == pArr)
    {
        perror("failed to allocate array");
        _exit(errno);
    }
    // printArr(pArr, totalElements);

    /* generate array */
    pArr = build_arr(totalElements);

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

    // create pInputs;
    for (size_t idx = 0; idx < nThreads; idx++)
    {
        (pThreadInput + idx)->pArr = pArr;
        (pThreadInput + idx)->start_index = nElementsPerThread * idx;
        (pThreadInput + idx)->nElements = nElementsPerThread;
        (pThreadInput + idx)->key = key;
        
        ret = pthread_create(pHndl + idx, NULL, search, (void *)(pThreadInput + idx));
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
        }
    }
    if(NULL == threadRet)
    {
        printf("Key not found\n");
    }
    else
    {
        printf("key found at index: %lu\n", (size_t)threadRet);
    }

    /* release resources */
    free(pThreadInput);
    free(pHndl);
    free(pArr);

    return (0);
}
