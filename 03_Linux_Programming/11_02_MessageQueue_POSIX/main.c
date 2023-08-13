#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>

#include "logger.h"

#define MESSAGE_QUEUE_PATH  "/msg_queue"

int main()
{
    struct mq_attr attr;
    mqd_t mqd;
    int ret = 0;
    char tx_buf[] = "Minh";
    unsigned int rx_buf_prio = 0;
    
    mqd = mq_open(MESSAGE_QUEUE_PATH, O_RDWR | O_CREAT | O_NONBLOCK, 0666, NULL);
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

    return 0;

    ret = mq_send(mqd, tx_buf, strlen(tx_buf), 0);
    ERROR_CHECK(ret, "mq_send()");
    ret = mq_send(mqd, tx_buf, strlen(tx_buf), 1);
    ERROR_CHECK(ret, "mq_send()");
    ret = mq_send(mqd, tx_buf, strlen(tx_buf), 2);
    ERROR_CHECK(ret, "mq_send()");
    ret = mq_send(mqd, tx_buf, strlen(tx_buf), 0);
    ERROR_CHECK(ret, "mq_send()");
    ret = mq_send(mqd, tx_buf, strlen(tx_buf), 2);
    ERROR_CHECK(ret, "mq_send()");

    printf("Received message:\n");
    
    char rx_buf[attr.mq_msgsize];
    while((ret = mq_receive(mqd, rx_buf, sizeof(rx_buf), &rx_buf_prio)) != -1)
    {
        printf("Priority %d: %s\n", rx_buf_prio, rx_buf);
    }

    ret = mq_unlink(MESSAGE_QUEUE_PATH);
    ERROR_CHECK(ret, "mq_unlink()");

    return 0;
}