#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#include "logger.h"

#define MESSAGE_QUEUE_PATH  "/msg_queue"

int main()
{
    struct mq_attr attr;
    mqd_t mqd;
    int ret = 0;
    
    mqd = mq_open(MESSAGE_QUEUE_PATH, O_CREAT, S_IRUSR | S_IWUSR, NULL);
    ERROR_CHECK(mqd, "mq_open()");

    ret = mq_getattr(mqd, &attr);
    ERROR_CHECK(ret, "mq_getattr()");

    if (attr.mq_flags == 0)  
        printf("mq_flags = 0\n");  
    else  
        printf("mq_flags = O_NONBLOCK\n");
    printf("mq_maxmsg = %ld,\n", attr.mq_maxmsg);  
    printf("mq_msgsize = %ld\n", attr.mq_msgsize);  
    printf("mq_curmsgs = %ld\n", attr.mq_curmsgs);

    

    ret = mq_unlink(MESSAGE_QUEUE_PATH);
    ERROR_CHECK(ret, "mq_unlink()");

    return 0;
}