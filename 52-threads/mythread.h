#ifndef _MY_THREAD_H_       
#define  _MY_THREAD_H_

/**
 * @file    mythread.h
 * @brief   header file for my thread implementation using pthread
 *
 * @author  Rohit Nimkar
 * @date    2023-06-11 09:17
 * @version 1.0
 */

typedef void *(*mythread_handler_t)(void *pArgs);
#include <pthread.h>


class MyThread {
public:
    MyThread(): handler(nullptr) {};
    MyThread(mythread_handler_t h): handler(h) {};
    int start(void *pArgs)
    {
        if (nullptr == handler) {
            return -1;
        }
        return pthread_create(&hndl, NULL, handler, pArgs);
    };

    int join(void **retVal)
    {
        return pthread_join(hndl, retVal);
    };
    ~MyThread() = default;

private:
    pthread_t hndl;
    mythread_handler_t handler;
};


#endif /* _MY_THREAD_H_ */
