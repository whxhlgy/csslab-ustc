#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>
#include <assert.h>

#define TODO()\
do{\
    extern int printf(char *, ...);\
    printf("Add your code here: file %s, line %d\n", __FILE__, __LINE__);\
}while(0)




atomic_int acnt;
int cnt;

void *start(void *thr_data) {
    // Exercise 2:
    // Add your code here:
    TODO();

    return NULL;
}

int main(void) {
    pthread_t pids[10];
    // Initialize atomic variable
    atomic_init(&acnt, 0);  
    cnt = 0;
    for (int n = 0; n < 10; ++n)
        pthread_create(&pids[n], NULL, start, NULL);
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