#ifndef ENV_H
#define ENV_H

#include "hash.h"

typedef struct env_t {
    hash_t hash;
    struct env_t* prev;
} env_t;

void env_init (env_t* env, env_t* prev);
sexpr_t* env_get (env_t* env, sym_t sym);
void env_put (env_t* env, sym_t sym, sexpr_t sexpr);

#endif