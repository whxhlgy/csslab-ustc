#include <stdio.h>
#include <pthread.h>

#define TODO()\
do{\
    extern int printf(char *, ...);\
    printf("Add your code here: file %s, line %d\n", __FILE__, __LINE__);\
}while(0)




#define N 100
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 5

struct buffer_t {
    pthread_mutex_t mutex;
    pthread_cond_t cond_full;
    pthread_cond_t cond_empty;
    long data[N];
    long size;
    long write_index;
    long read_index;
};

struct buffer_t buffer;

void initialize_buffer(struct buffer_t *buf) {
    pthread_mutex_init(&buf->mutex, NULL);
    pthread_cond_init(&buf->cond_full, NULL);
    pthread_cond_init(&buf->cond_empty, NULL);
}

void *producer(void *arg) {
    while(1) {
        // Exercise 5: solve the multi-producer multi-consumer problem
        // Add your code here:
        TODO();

    }
    pthread_exit(0);
}

void *consumer(void *arg) {
    while(1) {
        // Exercise 5: solve the multi-producer multi-consumer problem
        // Add your code here:
        TODO();

    }
    pthread_exit(0);
}

int main() {
    initialize_buffer(&buffer);

    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];

    for (long i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_create(&producers[i], NULL, producer, 0);
    }
    for (long i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_create(&consumers[i], NULL, consumer, 0);
    }
    for (long i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_join(producers[i], NULL);
    }
    for (long i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_join(consumers[i], NULL);
    }
    pthread_mutex_destroy(&buffer.mutex);
    pthread_cond_destroy(&buffer.cond_full);
    pthread_cond_destroy(&buffer.cond_empty);

    pthread_exit(0);
}
