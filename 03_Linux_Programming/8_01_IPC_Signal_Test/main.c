#define _POSIX_SOURCE
// #define _POSIX_C_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

static int sigchld_count = 0;
static int sigsegv_count = 0;
static int sigusr1_count = 0;

void sig_handler(int num)
{
    switch(num)
    {
        case SIGCHLD:
            printf("\n%d process detects SIGCHLD[%d] signal %d times.\n", getpid(), num, ++sigchld_count);
            wait(NULL);
            break;

        case SIGINT:
            printf("\nSIGINT[%d] detected\n", num);
            sleep(5);
            exit(EXIT_FAILURE);
            break;
        
        case SIGSEGV:
            printf("\n%d process detects SIGINT[%d] signal %d times.\n", getpid(), num, ++sigsegv_count);
            // exit(EXIT_FAILURE);
            break;

        case SIGUSR1:
            printf("\nSIGUSR1[%d] detected\n", num);
            // exit(EXIT_FAILURE);
        default:
            break;
    }
}

int main()
{
    // if(signal(SIGINT, sig_handler) == SIG_ERR)
    // {
    //     fprintf(stderr, "error: signal()\n");
    //     exit(EXIT_FAILURE);
    // }

    struct sigaction sa = {};
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);

    if(sigaction(SIGINT, &sa, NULL) == -1)
    {
        fprintf(stderr, "error: sigaction()\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGSEGV, sig_handler) == SIG_ERR)
    {
        fprintf(stderr, "error: signal()\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGUSR1, sig_handler) == SIG_ERR)
    {
        fprintf(stderr, "error: signal()\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGUSR1, sig_handler) == SIG_ERR)
    {
        fprintf(stderr, "error: signal()\n");
        exit(EXIT_FAILURE);
    }

        // if(kill(getpid(), SIGKILL) == -1)
        // {
        //     fprintf(stderr, "error kill()\n");
        //     exit(EXIT_FAILURE);
        // }

        /* Causing segmentation fault */
        // int *a = 0x0000000000000001;
        // *a = 10;
    // }
    
}