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
} thread_input_t;

void * thread_handler(void *pArgs)
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
    size_t nThreads = 4;
    size_t nElementsPerThread = 2500;
    size_t totalElements = 10000;
    int *pArr = NULL;
    void *threadRet = NULL;
    size_t sumFinal = 0;
    
    int ret = 0;
    pArr = build_arr(totalElements);
    if(NULL == pArr)
    {
        perror("failed to allocate array");
        _exit(errno);
    }

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
        
        ret = pthread_create(pHndl + idx, NULL, thread_handler, (void *)(pThreadInput + idx));
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
    printf("Final sum: %lu\n", sumFinal);

    /* release resources */
    free(pThreadInput);
    free(pHndl);
    free(pArr);

    return (0);
}
