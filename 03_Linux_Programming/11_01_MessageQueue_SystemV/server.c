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
    int key, msg_id;
    struct msg_buff msg;

    key = ftok(KEY_FILE_PATH, PROJ_ID);
    ERROR_CHECK(key, "ftok()");

    msg_id = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);
    ERROR_CHECK(msg_id, "msgget()");

    msg.msg_type = 300;
    strcpy(msg.msg_text, "Type 300");
    msgsnd(msg_id, &msg, sizeof(msg), 0);

    msg.msg_type = 200;
    strcpy(msg.msg_text, "Type 200");
    msgsnd(msg_id, &msg, sizeof(msg), 0);

    msg.msg_type = 100;
    strcpy(msg.msg_text, "Type 100");
    msgsnd(msg_id, &msg, sizeof(msg), 0);

    msg.msg_type = 400;
    strcpy(msg.msg_text, "Type 400");
    msgsnd(msg_id, &msg, sizeof(msg), 0);

    msg.msg_type = 100;
    strcpy(msg.msg_text, "Type 100");
    msgsnd(msg_id, &msg, sizeof(msg), 0);

    return 0;
}