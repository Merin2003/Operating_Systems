#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];  // Mutex for each fork

void *philosopher(void *arg) {
    int id = *(int *)arg;  // Get philosopher ID
    int left = id;         // Left fork index
    int right = (id + 1) % NUM_PHILOSOPHERS;  // Right fork index

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        // Pick up left fork
        pthread_mutex_lock(&forks[left]);
        printf("Philosopher %d picked up left fork %d.\n", id, left);

        // Pick up right fork
        pthread_mutex_lock(&forks[right]);
        printf("Philosopher %d picked up right fork %d and starts eating.\n", id, right);

        // Eating
        sleep(2);

        // Put down forks
        printf("Philosopher %d finished eating and put down forks.\n", id);
        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);
        
        sleep(1); // Thinking time before trying to eat again
    }
    return NULL;
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize mutexes (forks)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
