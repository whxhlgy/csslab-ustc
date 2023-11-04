#include <stdio.h>
#include <stdlib.h>
#include "lf-queue.h"

#define TODO()\
do{\
    extern int printf(char *, ...);\
    printf("Add your code here: file %s, line %d\n", __FILE__, __LINE__);\
}while(0)




void lf_queue_init(lf_queue_t *queue){
    node_t *node = (node_t *)calloc(1, sizeof(*node));
    atomic_store(&queue->front, node);
    atomic_store(&queue->rear, node);
    return;
}


void lf_queue_enqueue(lf_queue_t *queue, int value){
    // Exercise 2: fill in your code:
    // Add your code here:
    TODO();

    return;
}

int lf_queue_dequeue(lf_queue_t *queue){
    // Exercise 2: fill in your code:
    // Add your code here:
    TODO();

    return -1;
}

int lf_queue_size(lf_queue_t *queue){
    int size = 0;
    // Exercise 2: fill in your code:
    // Add your code here:
    TODO();

    return size;    
}
