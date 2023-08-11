#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <unistd.h>

#include "logger.h"

#define KEY_FILE_PATH       "./system_v_key/msg_key"
#define PROJ_ID             10

#define MAX_TRIES           10

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
#if defined(__linux__)
    struct seminfo *__buf;
#endif
};

int main()
{
    int key, sem_id;
    int ret = 0;

    key = ftok(KEY_FILE_PATH, PROJ_ID);
    ERROR_CHECK(key, "ftok()");

    sem_id = semget(key, 1, 0666 | IPC_CREAT | IPC_EXCL);

    if(sem_id != -1)
    {
        printf("Creating semaphore.\n");
        union semun sem_arg;
        struct sembuf sem_op = {};

        sem_arg.val = 0;
        ret = semctl(sem_id, 0, SETVAL, sem_arg);
        ERROR_CHECK(ret, "semctl()");

        sem_op.sem_op = 1;
        ret = semop(sem_id, &sem_op, 1);
        ERROR_CHECK(ret, "semop()");

    }
    else
    {
        printf("Opening semaphore.\n");

        union semun sem_arg;
        struct semid_ds sem_ds;
        struct sembuf sem_op = {};

        /* Check another errors of semaphore */
        if(errno != EEXIST)
        {
            fprintf(stderr, "Other errors.\n ");
            exit(EXIT_FAILURE);
        }

        /* Get ID of semaphore */
        sem_id = semget(key, 1, 0666);
        ERROR_CHECK(sem_id, "semget()");

        // sem_arg.val = 0;
        // ret = semctl(sem_id, 0, SETVAL, sem_arg);
        // ERROR_CHECK(ret, "semctl()");

        printf("sem_id = %d.\n", sem_id);

        sem_arg.buf = &sem_ds;
        for(int i = 0; i < MAX_TRIES; i++)
        {
            ret = semctl(sem_id, 0, IPC_STAT, sem_arg);
            ERROR_CHECK(ret, "semctl()");
            if(sem_ds.sem_otime != 0)
                break;
            sleep(1);
        }
        
        if(sem_ds.sem_otime == 0)
        {
            fprintf(stderr, "Semaphore not initialized.\n ");
            exit(EXIT_FAILURE);
        }
        
        ret = semctl(sem_id, 0, GETVAL, sem_arg);
        ERROR_CHECK(ret, "semctl()");

        if(sem_arg.val != 0)
        {
            printf("Semaphore's value is %d\n", sem_arg.val);
            // sem_op.sem_num = 0;
            // sem_op.sem_op = -1;
            // sem_op.sem_flg = 0;
            // ret = semop(sem_id, &sem_op, 1);
            // ERROR_CHECK(ret, "semop()");
        }
        else
        {
            printf("Semaphore's value is 0\n");
        }

        semctl(sem_id, 0, IPC_RMID);
        ERROR_CHECK(ret, "semctl()");

    }

    return 0;
}