#include <stdio.h>
#include <stdlib.h>
#include "lf-stack.h"

#define TODO()\
do{\
    extern int printf(char *, ...);\
    printf("Add your code here: file %s, line %d\n", __FILE__, __LINE__);\
}while(0)




void lf_stack_init(lf_stack_t *stack){
    atomic_store(&stack->top, NULL);
    return;
}

void lf_stack_push(lf_stack_t *stack, int value){
    // Exercise 1: lock-free stack.
    // Add your code here:
    Node_t *newNode = malloc(sizeof(Node_t));
    if (newNode == NULL) {
        printf("creat new node failed");
        return;
    }
    newNode->value = value;

    // Insert the new node onto the stack.
    Node_t *oldTop;
    do {
        oldTop = atomic_load(&stack->top);
        newNode->next = oldTop;
    } while (!atomic_compare_exchange_weak(&stack->top, &oldTop, newNode));
}

int lf_stack_pop(lf_stack_t *stack){
    // Exercise 1: lock-free stack
    // Add your code here:
    Node_t *oldTop;
    int value;
    do {
        oldTop = atomic_load(&stack->top);
        if (oldTop == NULL) {
            return -1;
        }
        value = oldTop->value;
    } while (!atomic_compare_exchange_weak(&stack->top, &oldTop, oldTop->next));

    free(oldTop);
    return value;
}



int lf_stack_size(lf_stack_t *stack){
    // Exercise 1: lock-free stack
    // Add your code here:
    int size = 0;
    Node_t *current = atomic_load(&stack->top);
    while (current) {
        size++;
        current = atomic_load(&current->next);
    }
    return size;
}

