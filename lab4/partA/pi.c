#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
struct arg_t {
    float x;
    float y;
};

void *start(void *arg) {
    // Exercise 2: Implement your code here
    // Add your code here:
    float x = ((struct arg_t*) arg)->x;
    float y = ((struct arg_t*) arg)->y;
    if (x*x + y*y < 1) {
        pthread_exit((void *)1);
    } else {
        pthread_exit((void *)0);
    }
}

int main(int argc, char **argv) {
    long N1 = atoll(argv[1]);
    pthread_t tids[N1];

    // pi(concurrency)
    for (long i = 0; i < N1; ++ i) {
        struct arg_t *arg = malloc(sizeof(*arg));
        int x = rand();
        int y = rand();
        arg->x = 1.0*x / RAND_MAX;
        arg->y = 1.0*y / RAND_MAX;
        pthread_create(&tids[i], 0, start, arg);
    }

    void *res;
    long M = 0;
    for (long i = 0; i < N1; ++ i) {
        pthread_join(tids[i], &res);
        M += (long)res;
    }
    printf("pai = %f\n", 4.0*M/N1);

    assert(4.0*M/N1 > 3.1 && 4.0*M/N1 < 3.2);  

    pthread_exit(0);
}
