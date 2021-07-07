#ifndef HASH_H
#define HASH_H

#include "sym.h"
#include "sexpr.h"

#define PRIME 11
#define BUCKET_SIZE 10 // FIXME should be dynamic

typedef struct {
    sym_t key;
    sexpr_t val;
} pair_t;

typedef struct hash_t {
    pair_t arrays [PRIME][BUCKET_SIZE];
    int lens [PRIME];
} hash_t;

void hash_init (hash_t* hash);
void hash_put (hash_t* hash, sym_t sym, sexpr_t sexpr);
sexpr_t* hash_get (hash_t* hash, sym_t sym);

#endif