
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
#define INCREMENTS 1000000

long long counter = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *increment_counter(void *arg)
{
    (void)arg;

    for (long long i = 0; i < INCREMENTS; i++)
    {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    clock_t start, end;

    start = clock();

    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_create(&threads[i], NULL,
                           increment_counter, NULL) != 0)
        {
            fprintf(stderr, "pthread_create failed\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            fprintf(stderr, "pthread_join failed\n");
            exit(EXIT_FAILURE);
        }
    }

    end = clock();

    printf("Expected counter value: %lld\n",
           (long long)NUM_THREADS * INCREMENTS);

    printf("Actual counter value: %lld\n", counter);

    printf("Execution time: %.6f seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    pthread_mutex_destroy(&lock);

    return 0;
}
