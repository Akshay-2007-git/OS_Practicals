#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE (100 * 1024 * 1024)

int main(void)
{
    char *data;

    /* Allocate 100 MB */
    data = malloc(SIZE);

    if (data == NULL)
    {
        perror("malloc");
        return 1;
    }

    /* Initialize memory */
    for (size_t i = 0; i < SIZE; i++)
    {
        data[i] = 1;
    }

    printf("Parent PID: %d\n", getpid());
    printf("Allocated and initialized 100 MB.\n");

    printf("\nMemory initialized.\n");
    printf("Press Enter to perform fork()...");
    getchar();

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        free(data);
        return 1;
    }

    if (pid == 0)
    {
        /* Child process */

        printf("\nChild PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
        printf("Child has inherited the memory.\n");

        printf("Press Enter before modifying memory...");
        getchar();

        /*
         * Modify one byte in every page.
         * This forces COW for the pages touched by the child.
         */
        for (size_t i = 0; i < SIZE; i += 4096)
        {
            data[i] = 2;
        }

        printf("\nChild modified one byte in every 4 KB page.\n");

        printf("Press Enter to exit child...");
        getchar();

        free(data);

        return 0;
    }
    else
    {
        /* Parent process */

        printf("\nParent PID: %d\n", getpid());
        printf("Child PID : %d\n", pid);

        printf("Parent and child initially share physical pages using COW.\n");

        printf("Press Enter to let the child modify memory...");
        getchar();

        wait(NULL);

        printf("\nChild has terminated.\n");

        free(data);
    }

    return 0;
}
