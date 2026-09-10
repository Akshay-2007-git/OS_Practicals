#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUM_CHILDREN 3
int main()
{
    pid_t child_pid[NUM_CHILDREN];
    pid_t pid;
    int status;
    printf("Parent Process: PID = %d\n\n", getpid());
    /* Create multiple child processes */
    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            /* Child process */
            printf("Child %d: PID = %d, PPID = %d\n",
                   i + 1, getpid(), getppid());
            /* Different execution times */
            sleep(i + 1);
            printf("Child %d: Completed\n", i + 1);
            exit((i + 1) * 10);
        }
        /* Store child PID in parent */
        child_pid[i] = pid;
    }
    printf("\n--- Using wait() ---\n");
    /*
     * wait() waits for any child process that terminates.
     */
    pid = wait(&status);
    if (pid > 0 && WIFEXITED(status))
    {
        printf("wait(): Child PID %d terminated "
               "with exit status %d\n",
               pid, WEXITSTATUS(status));
    }
    printf("\n--- Using waitpid() ---\n");
    /*
     * waitpid() waits for a specific child.
     * Here we wait for Child 2.
     */
    pid = waitpid(child_pid[1], &status, 0);
    if (pid > 0 && WIFEXITED(status))
    {
        printf("waitpid(): Child PID %d terminated "
               "with exit status %d\n",
               pid, WEXITSTATUS(status));
    }
    /*
     * Reap the remaining children.
     * waitpid() is used here to specifically
     * wait for Child 1 and Child 3.
     */
    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        if (child_pid[i] == pid)
            continue;
        pid = waitpid(child_pid[i], &status, 0);
        if (pid > 0 && WIFEXITED(status))
        {
            printf("waitpid(): Child PID %d terminated "
                   "with exit status %d\n",
                   pid, WEXITSTATUS(status));
        }
    }
    printf("\nParent: All children have completed.\n");
    return 0;
}
