#include <stdio.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERROR_CHECK(ret, msg)						    	\
do{	                                                    	\
	if((ret) == -1)								        	\
	{											        	\
		fprintf(stderr, "[%s:%d]: %s --> %s\n ", __FILE__,  \
                    __LINE__ - 1, msg, strerror(errno));	\
		exit(EXIT_FAILURE);						        	\
	}											        	\
} while(0)

#define KEY_FILE_PATH       "./system_v_key/msg_key"
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

    int msg_id = msgget(key, 0666 | IPC_CREAT);
    struct msqid_ds msqid;
    int ret = msgctl(msg_id, IPC_STAT, &msqid);
    ERROR_CHECK(ret, "msgctl()");

    printf("ID:\t\t%d\n", msg_id);
    printf("entry:\t\t%d\n", msg_id - msqid.msg_perm.__seq * 32768);
    printf("__seq:\t\t%d\n", msqid.msg_perm.__seq);

    return 0;
}