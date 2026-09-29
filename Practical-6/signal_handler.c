#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

volatile sig_atomic_t sigint_received = 0;
volatile sig_atomic_t sigterm_received = 0;
volatile sig_atomic_t sigusr1_received = 0;

/*
 * Signal handler
 */
void signal_handler(int signo)
{
    if (signo == SIGINT) {
        sigint_received = 1;
    }
    else if (signo == SIGTERM) {
        sigterm_received = 1;
    }
    else if (signo == SIGUSR1) {
        sigusr1_received = 1;
    }
}

int main()
{
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);

    /*
     * Register signal handlers
     */
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction SIGINT");
        exit(EXIT_FAILURE);
    }

    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("sigaction SIGTERM");
        exit(EXIT_FAILURE);
    }

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction SIGUSR1");
        exit(EXIT_FAILURE);
    }

    printf("Signal handling program started.\n");
    printf("Process PID = %d\n", getpid());

    printf("\nSend signals using:\n");
    printf("SIGINT : kill -SIGINT %d\n", getpid());
    printf("SIGTERM : kill -SIGTERM %d\n", getpid());
    printf("SIGUSR1 : kill -SIGUSR1 %d\n", getpid());

    while (1) {
        pause();

        if (sigint_received) {
            printf("\nSIGINT received!\n");
            printf("Interrupt signal handled.\n");
            sigint_received = 0;
        }

        if (sigusr1_received) {
            printf("SIGUSR1 received!\n");
            printf("User-defined event handled.\n");
            sigusr1_received = 0;
        }

        if (sigterm_received) {
            printf("SIGTERM received!\n");
            printf("Termination requested.\n");
            break;
        }
    }

    printf("Program terminating gracefully...\n");

    return 0;
}
