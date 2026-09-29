#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;
    int *malloc_ptr;
    int *calloc_ptr;
    int *temp;

    /* 1. malloc() */
    printf("1. malloc() demonstration\n");

    malloc_ptr = malloc(5 * sizeof(int));

    if (malloc_ptr == NULL)
    {
        printf("malloc() failed\n");
        return 1;
    }

    for (i = 0; i < 5; i++)
    {
        malloc_ptr[i] = (i + 1) * 10;
    }

    printf("Memory allocated using malloc():\n");

    for (i = 0; i < 5; i++)
    {
        printf("%d ", malloc_ptr[i]);
    }

    printf("\n\n");

    /* 2. calloc() */
    printf("2. calloc() demonstration\n");

    calloc_ptr = calloc(5, sizeof(int));

    if (calloc_ptr == NULL)
    {
        printf("calloc() failed\n");
        free(malloc_ptr);
        return 1;
    }

    printf("Memory allocated using calloc():\n");

    for (i = 0; i < 5; i++)
    {
        printf("%d ", calloc_ptr[i]);
    }

    printf("\n\n");

    /* 3. realloc() */
    printf("3. realloc() demonstration\n");

    temp = realloc(malloc_ptr, 10 * sizeof(int));

    if (temp == NULL)
    {
        printf("realloc() failed\n");
        free(malloc_ptr);
        free(calloc_ptr);
        return 1;
    }

    malloc_ptr = temp;

    for (i = 5; i < 10; i++)
    {
        malloc_ptr[i] = (i + 1) * 10;
    }

    printf("Memory after realloc():\n");

    for (i = 0; i < 10; i++)
    {
        printf("%d ", malloc_ptr[i]);
    }

    printf("\n\n");

    /* 4. free() */
    printf("4. free() demonstration\n");

    free(malloc_ptr);
    malloc_ptr = NULL;

    free(calloc_ptr);
    calloc_ptr = NULL;

    printf("Allocated memory successfully released.\n");

    return 0;
}
