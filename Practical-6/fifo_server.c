#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define SERVER_FIFO "/tmp/server_fifo"
#define MAX_MSG 256

typedef struct {
    pid_t client_pid;
    char message[MAX_MSG];
} Request;

typedef struct {
    char response[MAX_MSG];
} Response;

int main()
{
    int server_fd;
    Request request;
    char client_fifo[100];

    /* Create server FIFO */
    if (mkfifo(SERVER_FIFO, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    printf("Server started...\n");
    printf("Waiting for clients...\n");

    /*
     * Open server FIFO for reading.
     * O_RDWR prevents read() from receiving EOF when there are temporarily
     * no writers.
     */
    server_fd = open(SERVER_FIFO, O_RDWR);

    if (server_fd == -1) {
        perror("open");
        unlink(SERVER_FIFO);
        exit(EXIT_FAILURE);
    }

    while (1) {
        ssize_t n = read(server_fd, &request, sizeof(Request));

        if (n <= 0) {
            continue;
        }

        printf("\nReceived from Client PID %d: %s\n",
               request.client_pid, request.message);

        /* Create client's FIFO name */
        snprintf(client_fifo, sizeof(client_fifo),
                 "/tmp/client_%d_fifo", request.client_pid);

        int client_fd = open(client_fifo, O_WRONLY);

        if (client_fd == -1) {
            perror("open client FIFO");
            continue;
        }

        Response response;

        snprintf(response.response, sizeof(response.response),
                 "Server processed: %s",
                 request.message);

        write(client_fd, &response, sizeof(response));

        close(client_fd);

        printf("Response sent to Client PID %d\n",
               request.client_pid);
    }

    close(server_fd);
    unlink(SERVER_FIFO);

    return 0;
}
