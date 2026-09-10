#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2];
    pid_t pid1, pid2;
    /* Create pipe */
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    /* Create first child for ls */
    pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0)
    {
        /* Child 1: ls -l */
        close(pipefd[0]);   // Close unused read end
        /* Redirect stdout to pipe */
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        /* Execute ls -l */
        execlp("ls", "ls", "-l", (char *)NULL);

        perror("execlp ls");
        exit(EXIT_FAILURE);
    }
    /* Create second child for grep */
    pid2 = fork();
    if (pid2 < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid2 == 0)
    {
        /* Child 2: grep ".c" */
        close(pipefd[1]);   // Close unused write end
        /* Redirect stdin from pipe */
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        /* Execute grep ".c" */
        execlp("grep", "grep", ".c", (char *)NULL);
        perror("execlp grep");
        exit(EXIT_FAILURE);
    }

    /* Parent process */
    close(pipefd[0]);
    close(pipefd[1]);

    /* Wait for both children */
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Pipeline execution completed.\n");
    return 0;
}
