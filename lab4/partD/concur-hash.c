#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "concur-hash.h"

// hash
/* this is the D. J. Bernstein hash function */
static unsigned int djb_hash(const char *cp) {
    unsigned hash = 5381;
    while(*cp)
        hash = 33 * hash ^ (unsigned char) *cp++;
    return hash;
}

void hash_init(hash_t *ht, int num_buckets){
    pthread_mutex_init(&ht->mu, 0);
    ht->buckets = calloc(num_buckets, sizeof (*ht->buckets));
    ht->num_buckets = num_buckets;
}

void hash_insert(hash_t *ht, char *key, char *value) {
    // Exercise 2: complete the code below:
    // Add your code here:
    pthread_mutex_lock(&ht->mu);
    unsigned int hash = djb_hash(key) % ht->num_buckets;
    node_t *newNode = malloc(sizeof(node_t));
    if (newNode == NULL) {
        printf("failed to creat new Node!");
        pthread_mutex_unlock(&ht->mu);
    }
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->next = ht->buckets[hash];
    ht->buckets[hash] = newNode;
    pthread_mutex_unlock(&ht->mu);
}

char *hash_lookup(hash_t *ht, char *key) {
    pthread_mutex_lock(&ht->mu);
    unsigned int hash = djb_hash(key) % ht->num_buckets;
    node_t *bucket = ht->buckets[hash];
    while (bucket && strcmp(key, bucket->key) != 0) {
        bucket = bucket->next;
    }
    char *val = NULL;
    if (bucket != NULL) {
        val = bucket->value;
    }
    pthread_mutex_unlock(&ht->mu);
    return val;
}

// return 0 for success; 1 for non-exiting "key"
int hash_delete(hash_t *ht, char *key){
    pthread_mutex_lock(&ht->mu);
    unsigned int hash = djb_hash(key) % ht->num_buckets;
    node_t *pNode = ht->buckets[hash];
    node_t *last = pNode;
    while (pNode && strcmp(key, pNode->key) != 0) {
        last = pNode;
        pNode = pNode->next;
    }
    if (pNode == NULL) {
        return 1;
    }
    // deleting the matching node
    if (last == pNode) {
        ht->buckets[hash] = NULL;
    } else {
        last->next = pNode->next;
    }
    free(pNode);
    pthread_mutex_unlock(&ht->mu);
    return 0;
}

int hash_size(hash_t *ht){
    int size = 0;
    // Exercise 2: complete the code below:
    // Add your code here:
    pthread_mutex_lock(&ht->mu);
    for (int i = 0; i < ht->num_buckets; i++) {
        node_t *pNode = ht->buckets[i];
        while (pNode) {
            size++;
            pNode = pNode->next;
        }
    }
    pthread_mutex_unlock(&ht->mu);
    return size;
}
