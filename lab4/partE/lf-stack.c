#include <stdio.h>
#include <stdlib.h>
#include "lf-stack.h"

#define TODO()\
do{\
    extern int printf(char *, ...);\
    printf("Add your code here: file %s, line %d\n", __FILE__, __LINE__);\
}while(0)




void lf_stack_init(lf_stack_t *stack){
    atomic_store(&stack->top, 0);
    return;
}

void lf_stack_push(lf_stack_t *stack, int value){
    // Exercise 1: lock-free stack.
    // Add your code here:
    TODO();

}

int lf_stack_pop(lf_stack_t *stack){
    // Exercise 1: lock-free stack
    // Add your code here:
    TODO();

    return 0;
}



int lf_stack_size(lf_stack_t *stack){
    // Exercise 1: lock-free stack
    // Add your code here:
    TODO();

    return 0;
}

