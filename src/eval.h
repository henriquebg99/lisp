#ifndef EVAL_H
#define EVAl_H

#include "sexpr.h"
#include "env.h"

void eval (sexpr_t* out, sexpr_t* in, env_t* env);

#endif