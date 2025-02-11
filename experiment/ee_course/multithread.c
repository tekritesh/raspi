#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10   // Size of the shared buffer
#define NUM_PRODUCERS 2  // Number of producer threads
#define NUM_CONSUMERS 2  // Number of consumer threads

int buffer[BUFFER_SIZE];  // Shared buffer
int count = 0;            // Number of items in the buffer

// Mutex and condition variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_produce = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_consume = PTHREAD_COND_INITIALIZER;

// Producer function
void *producer(void *arg) {
    int id = *((int *)arg);
    free(arg);

    while (1) {
        int item = rand() % 100;  // Produce a random item

        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE) {
            // Buffer is full, wait for consumers
            pthread_cond_wait(&cond_produce, &mutex);
        }

        // Add item to buffer
        buffer[count] = item;
        count++;
        printf("Producer %d produced item: %d (Buffer count: %d)\n", id, item, count);

        pthread_cond_signal(&cond_consume);  // Signal a consumer
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 2);  // Simulate work
    }

    return NULL;
}

// Consumer function
void *consumer(void *arg) {
    int id = *((int *)arg);
    free(arg);

    while (1) {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            // Buffer is empty, wait for producers
            pthread_cond_wait(&cond_consume, &mutex);
        }

        // Remove item from buffer
        int item = buffer[count - 1];
        count--;
        printf("Consumer %d consumed item: %d (Buffer count: %d)\n", id, item, count);

        pthread_cond_signal(&cond_produce);  // Signal a producer
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 3);  // Simulate work
    }

    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&producers[i], NULL, producer, id);
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&consumers[i], NULL, consumer, id);
    }

    // Wait for threads to finish (they never will in this example)
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    return 0;
}
