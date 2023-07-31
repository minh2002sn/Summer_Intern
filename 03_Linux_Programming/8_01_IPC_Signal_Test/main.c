#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int sigint_count = 0;
static int sigusr1_count = 0;

void sig_handler(int num)
{
    switch(num)
    {
        case SIGINT:
            printf("\nSIGINT[%d] detected\n", num);
            exit(EXIT_FAILURE);
            break;
        
        case SIGSEGV:
            printf("\nSIGSEGV[%d] detected\n", num);
            exit(EXIT_FAILURE);
            break;

        case SIGUSR1:

        
        default:
            break;
    }
}

int main()
{
    if(signal(SIGINT, sig_handler) == SIG_ERR)
    {
        fprintf(stderr, "error: signal()\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGSEGV, sig_handler) == SIG_ERR)
    {
        fprintf(stderr, "error: signal()\n");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        printf("Hello from %d\n", getpid());
        sleep(2);

        if(kill(getpid(), SIGKILL) == -1)
        {
            fprintf(stderr, "error kill()\n");
            exit(EXIT_FAILURE);
        }

        /* Causing segmentation fault */
        // int *a = 0x0000000000000001;
        // *a = 10;
    }
    
}