#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_var = 100;
int global_uninitialized;
static int static_var = 200;

int main(void)
{
    int stack_var = 300;

    int *heap_var = malloc(sizeof(int));

    if (heap_var == NULL)
    {
        perror("malloc");
        return 1;
    }

    *heap_var = 400;

    printf("Process ID (PID): %d\n", getpid());
    printf("Address of code : %p\n", (void *)main);
    printf("Address of global : %p\n", (void *)&global_var);
    printf("Address of static : %p\n", (void *)&static_var);
    printf("Address of BSS : %p\n",
           (void *)&global_uninitialized);
    printf("Address of heap : %p\n", (void *)heap_var);
    printf("Address of stack : %p\n", (void *)&stack_var);

    printf("\nProcess is running...\n");

    while (1)
    {
        sleep(10);
    }

    free(heap_var);

    return 0;
}
