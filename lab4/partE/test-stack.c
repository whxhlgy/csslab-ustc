#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "lf-stack.h"

#define TODO()\
do{\
    extern int printf(char *, ...);\
    printf("Add your code here: file %s, line %d\n", __FILE__, __LINE__);\
}while(0)




#define TESTSIZE 1000

struct Lf_stack_t lf_stack;


void *work_stack_push(void *arg){
    for(int i=0; i<TESTSIZE; i++)
        lf_stack_push(&lf_stack, i);
}

void *work_stack_pop(void *arg){
    for(int i=0; i<TESTSIZE; i++)
        lf_stack_pop(&lf_stack);
}

int main(){
    lf_stack_init(&lf_stack);

     for(int i=0; i<TESTSIZE * 2; i++)
        lf_stack_push(&lf_stack, 1);
        
    pthread_t threads[4];
    for(int i=0; i<2; i++)
        pthread_create(&threads[i], NULL, work_stack_push, (void*)0);
    
    for(int i=2; i<4; i++)
        pthread_create(&threads[i], NULL, work_stack_pop, (void*)0);

    for(int i=0; i<4; i++)
        pthread_join(threads[i], NULL);
    
    int count = lf_stack_size(&lf_stack);
    assert(count==TESTSIZE * 2);

    printf("PASS!\n");
    return 0;
}