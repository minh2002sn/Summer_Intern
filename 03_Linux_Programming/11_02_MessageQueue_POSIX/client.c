#include <stdio.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/msg.h>

#include "logger.h"

#define KEY_FILE_PATH       "./system_v_key/msg_key"
#define PROJ_ID             10

#define BUFF_SIZE           255

struct msg_buff
{
    long msg_type;
    char msg_text[BUFF_SIZE];
};

int main()
{
    int key, msg_id, n;
    struct msg_buff msg;

    key = ftok(KEY_FILE_PATH, PROJ_ID);
    ERROR_CHECK(key, "ftok()");

    msg_id = msgget(key, 0666 | IPC_CREAT);
    ERROR_CHECK(msg_id, "msgget()");

    while((n = msgrcv(msg_id, &msg, sizeof(msg), 0, 0)))
    {
        printf("%d bytes data: %s\n", n, msg.msg_text);
    }

    return 0;
}