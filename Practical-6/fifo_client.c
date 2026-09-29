#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

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
    int server_fd, client_fd;
    char client_fifo[100];
    char message[MAX_MSG];

    Request request;
    Response response;

    pid_t pid = getpid();

    /* Create unique FIFO for this client */
    snprintf(client_fifo,
             sizeof(client_fifo),
             "/tmp/client_%d_fifo",
             pid);

    if (mkfifo(client_fifo, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    printf("Client PID: %d\n", pid);
    printf("Enter message: ");

    fgets(message, sizeof(message), stdin);

    /* Remove newline */
    message[strcspn(message, "\n")] = '\0';

    request.client_pid = pid;
    strcpy(request.message, message);

    /* Open server FIFO */
    server_fd = open(SERVER_FIFO, O_WRONLY);

    if (server_fd == -1) {
        perror("Unable to open server FIFO");
        unlink(client_fifo);
        exit(EXIT_FAILURE);
    }

    /* Send request */
    write(server_fd, &request, sizeof(request));
    close(server_fd);

    printf("Message sent to server.\n");

    /* Open client's FIFO for response */
    client_fd = open(client_fifo, O_RDONLY);

    if (client_fd == -1) {
        perror("Unable to open client FIFO");
        unlink(client_fifo);
        exit(EXIT_FAILURE);
    }

    /* Receive response */
    read(client_fd, &response, sizeof(response));

    printf("Server Response: %s\n", response.response);

    close(client_fd);

    /* Remove client's FIFO */
    unlink(client_fifo);

    return 0;
}
