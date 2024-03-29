#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

static int sigchld_count = 0;
static int sigsegv_count = 0;
static int sigusr1_count = 0;

void sig_handler(int num)
{
    switch(num)
    {
        case SIGPIPE:
            printf("Writing a pipe locking close end.\n");
            exit(EXIT_FAILURE);

        case SIGCHLD:
            printf("\n%d process detects SIGCHLD[%d] signal %d times.\n", getpid(), num, ++sigchld_count);
            wait(NULL);
            break;

        case SIGINT:
            printf("\n%d process detects SIGINT[%d] signal\n", getpid(), num);
            exit(EXIT_FAILURE);
            break;
        
        case SIGSEGV:
            printf("\n%d process detects SIGINT[%d] signal %d times.\n", getpid(), num, ++sigsegv_count);
            // exit(EXIT_FAILURE);
            break;

        case SIGUSR1:
            printf("\n%d process detects SIGINT[%d] signal %d times.\n", getpid(), num, ++sigusr1_count);
            break;
        
        default:
            break;
    }
}

int main()
{
    // if(signal(SIGPIPE, sig_handler) == SIG_ERR)
    // {
    //     fprintf(stderr, "error: signal()\n");
    //     exit(EXIT_FAILURE);
    // }


    int pipe_fd[2];
    if(pipe(pipe_fd) == -1)
    {
        fprintf(stderr, "error: signal()\n");
        exit(EXIT_FAILURE);
    }

    printf("Pipe buffer size: %d\n", fcntl(pipe_fd[1], F_GETPIPE_SZ));

    int flags = fcntl(pipe_fd[0], F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(pipe_fd[0], F_SETFL, flags);

    close(pipe_fd[1]);
    int buff[1] = {};
    int ret = 0;
    if((ret = read(pipe_fd[0], buff, 1)) == 0)
    {
        printf("No data in pipe.\n");
    }
    else
    {
        printf("Data: %d\n", buff[0]);
    }
    printf("ret = %d\n", ret);
    // if(write(pipe_fd[1], buff, 1) != 0)
    //     printf("Writing pipe error is detected");

    while(1)
    {
        printf("Hello from parent process (%d).\n", getpid());
        // kill(getpid(), SIGSEGV);
        sleep(2);

        // if(kill(getpid(), SIGKILL) == -1)
        // {
        //     fprintf(stderr, "error kill()\n");
        //     exit(EXIT_FAILURE);
        // }

        /* Causing segmentation fault */
        // int *a = 0x0000000000000001;
        // *a = 10;
    }
    
}