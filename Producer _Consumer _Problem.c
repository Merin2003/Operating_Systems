#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Buffer size

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0, out = 0;     // Circular buffer indices
int count = 0;           // Number of items in the buffer

void *producer(void *arg) 
{
    int produced_items = *((int *)arg);
    for (int i = 1; i <= produced_items; i++) {
        // Wait until there is space in the buffer
        while (count == BUFFER_SIZE); // Busy wait (inefficient)

        buffer[in] = i;  // Produce item
        printf("Produced: %d\n", i);
        in = (in + 1) % BUFFER_SIZE; // Move circular buffer index

        count++; // Increase item count

        usleep(100000); // Simulate processing delay
    }
    return NULL;
}

void *consumer(void *arg) {
    int consumed_items = *((int *)arg);
    for (int i = 1; i <= consumed_items; i++) {
        // Wait until there is an item to consume
        while (count == 0); // Busy wait (inefficient)

        int item = buffer[out]; // Consume item
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE; // Move circular buffer index

        count--; // Decrease item count

        usleep(150000); // Simulate processing delay
    }
    return NULL;
}

int main() 
{
    int num_items;
    printf("Enter the number of items to produce/consume: ");
    scanf("%d", &num_items);

    pthread_t prod_thread, cons_thread;

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, &num_items);
    pthread_create(&cons_thread, NULL, consumer, &num_items);

    // Wait for both threads to complete
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    return 0;
}
