#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <unistd.h>

#include "logger.h"

#define KEY_FILE_PATH       "./system_v_key/shm_key"
#define PROJ_ID             10

int main()
{
    int key, shm_id;
    int ret = 0;

    key = ftok(KEY_FILE_PATH, PROJ_ID);
    ERROR_CHECK(key, "ftok()");
    printf("key = %d\n", key);

    shm_id = shmget(key, 1024, 0666 | IPC_CREAT | IPC_EXCL);

    if(shm_id != -1)
    {
        char *p_shm;

        printf("Creating shared memory.\n");

        p_shm = shmat(shm_id, NULL, 0);
        ERROR_CHECK((long int)p_shm, "shmat()");

        strcpy(p_shm, "PIF");

        // ret = shmdt(p_shm);
        // ERROR_CHECK(ret, "shmdt()");
    }
    else
    {
        char *p_shm;

        printf("using exist shared memory.\n");

        if(errno != EEXIST)
        {
            fprintf(stderr, "Other errors.\n ");
            exit(EXIT_FAILURE);
        }

        shm_id = shmget(key, 1024, 0666);
        ERROR_CHECK(shm_id, "shmget()");

        p_shm = shmat(shm_id, NULL, 0);
        ERROR_CHECK((long int)p_shm, "shmat()");

        printf("Shared memory's data: %s\n", p_shm);

        ret = shmctl(shm_id, IPC_RMID, NULL);
        ERROR_CHECK(ret, "shmctl()");
    }

    return 0;
}