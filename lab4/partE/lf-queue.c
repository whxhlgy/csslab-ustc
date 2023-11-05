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
    node_t *newNode = calloc(1, sizeof(node_t));
    newNode->value = value;
    node_t *oldRear;
    node_t *nullPtr = NULL;
    do { // CAS operation
        oldRear = atomic_load(&queue->rear);
    } while (!atomic_compare_exchange_weak(&oldRear->next, &nullPtr, newNode));
    atomic_compare_exchange_weak(&queue->rear, &oldRear, newNode);   // don't need a loop, because there always
                                                                     // be a thread set the rear correctly
    return;
}

int lf_queue_dequeue(lf_queue_t *queue){
    // Exercise 2: fill in your code:
    // Add your code here:
    node_t* front;
    node_t* rear;
    node_t* next;
    int value;

    do {
        front = atomic_load(&queue->front);
        rear = atomic_load(&queue->rear);
        next = atomic_load(&front->next);
        value = next->value;

        if (front == rear) {
            return -1;
        } else if (front->next == rear){
            atomic_compare_exchange_weak(&queue->rear, &rear, front);
        }
    } while (!atomic_compare_exchange_weak(&queue->front, &front, next));

    free(front); // Free the old dummy node
    return value;
}

int lf_queue_size(lf_queue_t *queue){
    int size = 0;
    node_t* current = atomic_load(&queue->front);
    node_t* tail = atomic_load(&queue->rear);

    while (current != tail) {
        size++;
        current = atomic_load(&current->next);
    }
    return size;
}
