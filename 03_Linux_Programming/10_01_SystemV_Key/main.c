#include <stdio.h>
#include <sys/ipc.h>
#include <sys/stat.h>

#define KEY_FILE_PATH       "./system_v_key/sem_key"
#define PROJ_ID             10

int main()
{
    int key = ftok(KEY_FILE_PATH, PROJ_ID);
    struct stat st;
    stat(KEY_FILE_PATH, &st);

    printf("Key:\t\t0x%08X\n", key);
    printf("__proj_id:\t0x%08X\n", (unsigned int)(PROJ_ID & 0x000000FF) << (8 * 3));
    printf("Device id:\t0x%08X\n", (unsigned int)(st.st_dev & 0x000000FF) << (8 * 2));
    printf("I-node:\t\t0x%08X\n", (unsigned int)(st.st_ino & 0x0000FFFF));

    return 0;
}