#include "env.h"
#include <stdlib.h>

void env_init (env_t* env, env_t* prev) {
    hash_init(&(env->hash));
    env->prev = prev;
}

sexpr_t* env_get (env_t* env, sym_t sym) {
    sexpr_t* sexpr = hash_get(&(env->hash), sym);

    if (sexpr == NULL && env->prev != NULL) {
        return env_get(env->prev, sym);
    } else {
        return sexpr;
    }
}

void env_put (env_t* env, sym_t sym, sexpr_t sexpr) {
    hash_put(& (env->hash), sym, sexpr);
}