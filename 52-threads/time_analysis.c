#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
    time_t t  = {0};
    struct tm *pTm =  NULL;
    t = time(NULL);
    
    pTm = localtime(&t);

    printf("current time: %s\n", ctime(&t));



    return 0;
}

