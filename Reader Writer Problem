#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;       // To protect read_count
sem_t rw_mutex;    // To provide exclusive access to writers
int read_count = 0;
int data = 0;      // Shared resource

void* reader(void* arg) {
    int id = (int)arg;

    sem_wait(&mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&rw_mutex);  // First reader locks writers
    }
    sem_post(&mutex);

    // Reading
    printf("Reader %d: read data = %d\n", id, data);
    sleep(1);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&rw_mutex);  // Last reader unlocks writers
    }
    sem_post(&mutex);

    return NULL;
}

void* writer(void* arg) {
    int id = (int)arg;

    sem_wait(&rw_mutex);

    // Writing
    data += 10;
    printf("Writer %d: wrote data = %d\n", id, data);
    sleep(2);

    sem_post(&rw_mutex);

    return NULL;
}

int main() {
    int n_readers, n_writers;

    printf("Enter number of readers: ");
    scanf("%d", &n_readers);

    printf("Enter number of writers: ");
    scanf("%d", &n_writers);

    pthread_t readers[n_readers], writers[n_writers];
    int r_id[n_readers], w_id[n_writers];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < n_readers; i++) {
        r_id[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &r_id[i]);
    }

    // Create writer threads
    for (int i = 0; i < n_writers; i++) {
        w_id[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &w_id[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < n_readers; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < n_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    // Cleanup
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}
