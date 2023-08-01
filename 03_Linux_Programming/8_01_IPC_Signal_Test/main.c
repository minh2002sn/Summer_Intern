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
    int child_pid = 0;
    sigset_t new_set;
    sigemptyset(&new_set);
    sigaddset(&new_set, SIGSEGV);
    sigaddset(&new_set, SIGUSR1);
    sigaddset(&new_set, SIGCHLD);
    // sigprocmask(SIG_BLOCK, &new_set, NULL);
    
    // if(signal(SIGCHLD, sig_handler) == SIG_ERR)
    // {
    //     fprintf(stderr, "error: signal()\n");
    //     exit(EXIT_FAILURE);
    // }

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

    if(signal(SIGUSR1, sig_handler) == SIG_ERR)
    {
        fprintf(stderr, "error: signal()\n");
        exit(EXIT_FAILURE);
    }

    // kill(getpid(), SIGSEGV);
    // kill(getpid(), SIGSEGV);
    // kill(getpid(), SIGSEGV);
    // kill(getpid(), SIGUSR1);
    // kill(getpid(), SIGUSR1);
    // kill(getpid(), SIGUSR1);
    // sigprocmask(SIG_UNBLOCK, &new_set, NULL);

    printf("Hello from parent process (%d).\n", getpid());

    if((child_pid = fork()) == -1)
    {
        fprintf(stderr, "error: signal()\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        if(child_pid == 0)
        {
            printf("Hello from child process (%d).\n", getpid());
            sleep(2);
            exit(EXIT_FAILURE);
        }
    }

    if((child_pid = fork()) == -1)
    {
        fprintf(stderr, "error: signal()\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        if(child_pid == 0)
        {
            printf("Hello from child process (%d).\n", getpid());
            sleep(2);
            exit(EXIT_FAILURE);
        }
    }

    if((child_pid = fork()) == -1)
    {
        fprintf(stderr, "error: signal()\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        if(child_pid == 0)
        {
            printf("Hello from child process (%d).\n", getpid());
            sleep(1);
            char pid_str[8] = {};
            sprintf(pid_str, "%d", getppid());
            // execl("/bin/ps", "--ppid", pid_str, NULL);
            execl("/bin/ps", pid_str, NULL);
        }
    }

    if(signal(SIGCHLD, sig_handler) == SIG_ERR)
    {
        fprintf(stderr, "error: signal()\n");
        exit(EXIT_FAILURE);
    }

    sleep(5);
    // sigprocmask(SIG_UNBLOCK, &new_set, NULL);

    if((child_pid = fork()) == -1)
    {
        fprintf(stderr, "error: signal()\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        if(child_pid == 0)
        {
            printf("Hello from child process (%d).\n", getpid());
            sleep(1);
            char pid_str[8] = {};
            sprintf(pid_str, "%d", getppid());
            // execl("/bin/ps", "--ppid", pid_str, NULL);
            execl("/bin/ps", pid_str, NULL);
        }
    }

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