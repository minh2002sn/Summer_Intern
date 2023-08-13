#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>
#include "logger.h"

static sem_t sem;

int main()
{
    int ret = 0;
    int sem_val = 0;

    ret = sem_init(&sem, 1, 1);
    ERROR_CHECK(ret, "sem_init()");

    printf("Semaphore was created.\n");

    ret = sem_getvalue(&sem, &sem_val);
    ERROR_CHECK(ret, "sem_getvalue()");
    printf("Semaphore's value: %d\n", sem_val);

    // ret = sem_post(sem);
    // ERROR_CHECK(ret, "sem_post()"); 
    ret = sem_getvalue(&sem, &sem_val);
    ERROR_CHECK(ret, "sem_getvalue()");
    printf("Semaphore's value after run post(): %d\n", sem_val);

    while(sem_val > 0)
    {
        ret = sem_wait(&sem);
        ERROR_CHECK(ret, "sem_wait()");
        ret = sem_getvalue(&sem, &sem_val);
        ERROR_CHECK(ret, "sem_getvalue()");
        printf("Semaphore's value: %d\n", sem_val);
    }

    ret = sem_destroy(&sem); 
    ERROR_CHECK(ret, "semm_destroy()");

    return 0;
}