#include "hash.h"
#include <stdlib.h>

void hash_init (hash_t* hash) {
    int i;

    for (i = 0; i < PRIME; i++) {
        hash->lens[i] = 0;
    }
}

void hash_put (hash_t* hash, sym_t sym, sexpr_t sexpr) {
    int bucket = sym % PRIME;

    if (hash->lens[bucket] == BUCKET_SIZE) {
        // error 
    } else {
        hash->arrays[bucket][hash->lens[bucket]].key = sym;
        hash->arrays[bucket][hash->lens[bucket]].val = sexpr;
        hash->lens[bucket]++;
    }
}

sexpr_t* hash_get (hash_t* hash, sym_t sym) {
    int i, bucket = sym % PRIME;
    
    for (i = 0; i < hash->lens[bucket]; i++) {
        if (hash->arrays[bucket][i].key == sym) {
            return & (hash->arrays[bucket][i].val);
        }
    }

    return NULL;
}