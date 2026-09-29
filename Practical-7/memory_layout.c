#include <stdio.h>
#include <stdlib.h>

/* Global variables */
int global_var = 10;
int global_uninit;

/* Function Code/Text segment */
void display_code_address(void)
{
    printf("Code address : %p\n",
           (void *)display_code_address);
}

int main(void)
{
    /* Static variable */
    static int static_var = 20;

    /* Local variable - Stack */
    int stack_var = 30;

    /* Dynamic memory - Heap */
    int *heap_var = (int *)malloc(sizeof(int));

    if (heap_var == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    *heap_var = 40;

    printf("===== Linux Process Address Space =====\n\n");

    /* Code/Text segment */
    display_code_address();

    /* Data segment */
    printf("Global address : %p\n",
           (void *)&global_var);

    /* Static variable */
    printf("Static address : %p\n",
           (void *)&static_var);

    /* BSS segment */
    printf("BSS address : %p\n",
           (void *)&global_uninit);

    /* Heap */
    printf("Heap address : %p\n",
           (void *)heap_var);

    /* Stack */
    printf("Stack address : %p\n",
           (void *)&stack_var);

    free(heap_var);

    return 0;
}
