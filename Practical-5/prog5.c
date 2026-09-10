#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#define NUM_MESSAGES 10000
#define MESSAGE_SIZE 100
int main()
{
    int pipefd[2];
    pid_t pid;
    char message[MESSAGE_SIZE];
    char buffer[MESSAGE_SIZE];
    struct timespec start, end;
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    /* Child Process - Consumer */
    if (pid == 0)
    {
        close(pipefd[1]);   // Close unused write end
        int count = 0;
        while (read(pipefd[0], buffer, MESSAGE_SIZE) > 0)
        {
            count++;
        }
        close(pipefd[0]);
        printf("Consumer: Received %d messages\n", count);
        exit(0);
    }
    /* Parent Process - Producer */
    else
    {
        close(pipefd[0]);   // Close unused read end
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < NUM_MESSAGES; i++)
        {
            snprintf(message, MESSAGE_SIZE, "Message %d from Producer", i + 1);
            if (write(pipefd[1], message, MESSAGE_SIZE) == -1)
            {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
        close(pipefd[1]);
        wait(NULL);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        long total_bytes = (long)NUM_MESSAGES * MESSAGE_SIZE;
        double throughput = total_bytes / elapsed / (1024 * 1024);
        printf("\nProducer: Sent %d messages\n", NUM_MESSAGES);
        printf("Total data transferred : %ld bytes\n", total_bytes);
        printf("Communication time     : %.6f seconds\n", elapsed);
        printf("Communication throughput: %.2f MB/s\n", throughput);
    }
    return 0;
}
