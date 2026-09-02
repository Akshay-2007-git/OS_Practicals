
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    printf("Initial State:\n");
    printf("Process PID  : %d\n", getpid());
    printf("Parent PPID   : %d\n", getppid());
    printf("Process State : Running\n\n");

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }

    else if (pid == 0)
    {
        /* Child Process */
        printf("Child Process:\n");
        printf("PID           : %d\n", getpid());
        printf("PPID          : %d\n", getppid());
        printf("Process State : Running\n");

        sleep(3);

        printf("\nChild Process after sleep:\n");
        printf("PID           : %d\n", getpid());
        printf("PPID          : %d\n", getppid());
        printf("Process State : Running\n");

        printf("\nChild Process terminating...\n");
        exit(0);
    }

    else
    {
        /* Parent Process */
        printf("Parent Process:\n");
        printf("PID           : %d\n", getpid());
        printf("PPID          : %d\n", getppid());
        printf("Child PID     : %d\n", pid);
        printf("Process State : Running\n");

        sleep(1);

        printf("\nParent Process waiting for child...\n");
        printf("Process State : Waiting/Blocked\n");

        wait(NULL);

        printf("\nParent Process after child termination:\n");
        printf("PID           : %d\n", getpid());
        printf("PPID          : %d\n", getppid());
        printf("Process State : Running\n");

        printf("\nParent Process terminating...\n");
    }

    return 0;
}
