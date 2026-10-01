#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;

    /* Open output file */
    fd = open("output.txt",
              O_WRONLY | O_CREAT | O_TRUNC,
              0644);

    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Before redirection\n");

    /* Redirect stdout (fd 1) to output.txt */
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    /* These outputs now go to output.txt */
    printf("Hello from redirected standard output!\n");
    printf("This message is stored in output.txt\n");

    return 0;
}
