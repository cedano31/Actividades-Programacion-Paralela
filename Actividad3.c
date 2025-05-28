#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_THREADS 5
#define INCREMENTS 1000

//Gabriel Cedano 24-1242

int shared_variable = 0;
sem_t semaphore;

void* increment(void* arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        sem_wait(&semaphore);
        shared_variable++;
        sem_post(&semaphore);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    sem_init(&semaphore, 0, 1);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);
    printf("Valor final de la variable compartida: %d\n", shared_variable);
    return 0;
}