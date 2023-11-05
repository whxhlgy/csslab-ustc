#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>
#include <assert.h>


atomic_int acnt;
int cnt;

void *start(void *thr_data) {
    // Exercise 2:
    // Add your code here:
    for (int i = 0; i < 10000; i++) {
        atomic_fetch_add(&acnt, 1);
        cnt += 1;
    }
    return NULL;
}

int main(void) {
    pthread_t pids[10];
    // Initialize atomic variable
    atomic_init(&acnt, 0);  
    cnt = 0;
    for (int n = 0; n < 10; ++n)
        pthread_create(&pids[n], NULL, start, (void *)10000L);
    for (int n = 0; n < 10; ++n)
        pthread_join(pids[n], NULL);

    int atomic_cnt = atomic_load(&acnt);  // Load atomic variable
    printf("The atomic counter is %d\n", atomic_cnt);
    printf("The non-atomic counter is %d\n", cnt);

    int expected = 100000;
    assert(acnt == expected);
    printf("Testing atomic variables: PASS\n");
    return 0;
}