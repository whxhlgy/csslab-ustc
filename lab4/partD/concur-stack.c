#include <stdio.h>
#include <stdlib.h>
#include "concur-stack.h"


void concur_stack_init(concur_stack_t *stack){
    pthread_mutex_init(&stack->mu, NULL);
    return;
}

void concur_stack_push(concur_stack_t *stack, int value){
    pthread_mutex_lock(&stack->mu);
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    newNode->next = stack->top;
    newNode->value = value;
    stack->top = newNode;
    pthread_mutex_unlock(&stack->mu);
}

int concur_stack_pop(concur_stack_t *stack){
    int value = -1;
    pthread_mutex_lock(&stack->mu);
    if (stack->top) {
        node_t *top = stack->top;
        value = top->value;
        stack->top = top->next;
    }
    pthread_mutex_unlock(&stack->mu);
    return value;
}

int concur_stack_size(concur_stack_t *stack){
    pthread_mutex_lock(&stack->mu);
    int size = 0;
    node_t *node = stack->top;
    while (node)
    {
        node = node->next;
        size += 1;
    }
    pthread_mutex_unlock(&stack->mu);
    return size;
}