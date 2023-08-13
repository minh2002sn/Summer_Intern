#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>
#include "logger.h"

#define SEM_PATH            "/sem_file"

int main()
{
    sem_t *sem;
    int ret = 0;
    int sem_val = 0;

    sem = sem_open(SEM_PATH, O_CREAT | O_EXCL, 0666, 2);
    
    if(sem != SEM_FAILED)
    {
        printf("Creating a semaphore.\n");
        ret = sem_getvalue(sem, &sem_val);
        ERROR_CHECK(ret, "sem_getvalue()");

        printf("Semaphore's value: %d\n", sem_val);

        ret = sem_close(sem);
    }
    else
    {
        printf("Semaphore was created");

        if(errno != EEXIST)
        {
            exit(EXIT_FAILURE);
        }

        sem = sem_open(SEM_PATH, 0);

        ret = sem_getvalue(sem, &sem_val);
        ERROR_CHECK(ret, "sem_getvalue()");
        printf("Semaphore's value: %d\n", sem_val);

        ret = sem_post(sem);
        ERROR_CHECK(ret, "sem_post()"); 
        ret = sem_getvalue(sem, &sem_val);
        ERROR_CHECK(ret, "sem_getvalue()");
        printf("Semaphore's value after run post(): %d\n", sem_val);

        while(sem_val > 0)
        {
            ret = sem_wait(sem);
            ERROR_CHECK(ret, "sem_wait()");
            ret = sem_getvalue(sem, &sem_val);
            ERROR_CHECK(ret, "sem_getvalue()");
            printf("Semaphore's value: %d\n", sem_val);
        }

        ret = sem_unlink(SEM_PATH); 
        ERROR_CHECK(ret, "semm_unlink()");
    }

    return 0;
}