#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO()\
do{\
    extern int printf(char *, ...);\
    printf("Add your code here: file %s, line %d\n", __FILE__, __LINE__);\
}while(0)




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
    TODO();

}

char *hash_lookup(hash_t *ht, char *key) {
    // Exercise 2: complete the code below:
    // Add your code here:
    TODO();

}

// return 0 for success; 1 for non-exiting "key"
int hash_delete(hash_t *ht, char *key){
    // Exercise 2: complete the code below:
    // Add your code here:
    TODO();

    return 1;
}

int hash_size(hash_t *ht){
    int size = 0;
    // Exercise 2: complete the code below:
    // Add your code here:
    TODO();

    return size;
}
