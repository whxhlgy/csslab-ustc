#include <stdio.h>
#include <stdlib.h>
#include "concur-stack.h"

#define TODO()\
do{\
    extern int printf(char *, ...);\
    printf("Add your code here: file %s, line %d\n", __FILE__, __LINE__);\
}while(0)




void concur_stack_init(concur_stack_t *stack){
    pthread_mutex_init(&stack->mu, NULL);
    return;
}

void concur_stack_push(concur_stack_t *stack, int value){
    // Exercise 1: complete other operations of the concurrent stack.
    // Add your code here:
    TODO();

}

int concur_stack_pop(concur_stack_t *stack){
    int value = -1;
    // Exercise 1: complete other operations of the concurrent stack.
    // Add your code here:
    TODO();

    return value;
}

int concur_stack_size(concur_stack_t *stack){
    int size = 0;
    // Exercise 1: complete other operations of the concurrent stack.
    // Add your code here:
    TODO();

    return size;
}
