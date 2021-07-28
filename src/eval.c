#include "eval.h"
#include <stdlib.h>

void eval_plus (sexpr_t* out, sexpr_t* in, env_t* env) {
    sexpr_t *arg1 = CADR(in), *arg2;
    sexpr_t v1, v2;

    if (!IS_CONS(CDR(CDR(in)))) {
        // error;
    }

    arg2 = CAR(CDR(CDR(in)));

    eval(&v1, arg1, env);
    eval(&v2, arg2, env);

    if (!(IS_INTEGER(&v1) && IS_INTEGER(&v2))) {
        // error;
    }

    MK_INTEGER(out, INTEGER(&v1) + INTEGER(&v2));
}

void eval_times (sexpr_t* out, sexpr_t* in, env_t* env) {
    sexpr_t *arg1 = CADR(in), *arg2;
    sexpr_t v1, v2;

    if (!IS_CONS(CDR(CDR(in)))) {
        // error;
    }

    arg2 = CAR(CDR(CDR(in)));

    eval(&v1, arg1, env);
    eval(&v2, arg2, env);

    if (!(IS_INTEGER(&v1) && IS_INTEGER(&v2))) {
        // error;
    }

    MK_INTEGER(out, INTEGER(&v1) * INTEGER(&v2));
}

void eval_minus (sexpr_t* out, sexpr_t* in, env_t* env) {
    sexpr_t *arg1 = CADR(in), *arg2;
    sexpr_t v1, v2;

    if (!IS_CONS(CDR(CDR(in)))) {
        // error;
    }

    arg2 = CAR(CDR(CDR(in)));

    eval(&v1, arg1, env);
    eval(&v2, arg2, env);

    if (!(IS_INTEGER(&v1) && IS_INTEGER(&v2))) {
        // error;
    }

    MK_INTEGER(out, INTEGER(&v1) - INTEGER(&v2));
}

void eval_eq (sexpr_t* out, sexpr_t* in, env_t* env) {
    sexpr_t *arg1 = CADR(in), *arg2;
    sexpr_t v1, v2;

    if (!IS_CONS(CDR(CDR(in)))) {
        // error;
    }

    arg2 = CAR(CDR(CDR(in)));

    eval(&v1, arg1, env);
    eval(&v2, arg2, env);

    if (v1.type == v2.type) { 
        if (IS_CONS(&v1) && CAR(&v1) == CAR(&v2) && CDR(&v1) == CDR(&v2)) {
            MK_TRUE(out);
        } else if (IS_ATOM(&v1) && (
                    (IS_INTEGER(&v1) && INTEGER(&v1) == INTEGER(&v2)) ||
                    (IS_SYMBOL(&v1) && SYMBOL(&v1) == SYMBOL(&v2))    ||
                    (IS_NIL(&v1) && IS_NIL(&v2))                      ||
                    (IS_BOOL(&v1) && IS_TRUE(&v1) == IS_TRUE(&v2))    )) {
            MK_TRUE(out);
        } else
            MK_FALSE(out);
    } else
        MK_FALSE(out);
}

void eval_cons (sexpr_t* out, sexpr_t* in, env_t* env) {
    sexpr_t *arg1 = CADR(in), *arg2;
    sexpr_t *v1 = sexpr_alloc(), *v2 = sexpr_alloc();

    if (!IS_CONS(CDR(CDR(in)))) {
        // error;
    }

    arg2 = CAR(CDR(CDR(in)));

    eval(v1, arg1, env);
    eval(v2, arg2, env);

    MK_CONS(out, v1, v2);
}

void eval_if (sexpr_t* out, sexpr_t* in, env_t* env) {
    // TODO check and show erros
    sexpr_t* guard_exp = CADR(in), guard_val;
    sexpr_t* then_exp = CAR(CDDR(in));
    sexpr_t* else_exp = CAR(CDR(CDDR(in)));

    eval(&guard_val, guard_exp, env);

    if (IS_BOOL(&guard_val)) {
        if (IS_TRUE(&guard_val)) {
            eval(out, then_exp, env);
        } else {
            eval(out, else_exp, env);
        }
    } else {
        // error
    }
}

void eval_function_call (sexpr_t* out, sexpr_t* lambda, sexpr_t* args, env_t* env) {
    sexpr_t *params = CADR(lambda);
    sexpr_t *body = CAR(CDDR(lambda));

    env_t new_env;
    env_init(&new_env, env);

    sexpr_t *next_par = params, *next_arg = args;

    while (!IS_NIL(next_par) && !IS_NIL(next_arg)) {
        if (!IS_CONS(next_par) || !IS_CONS(next_arg)) {
            // error
        } else {
            // eval arguments; TODO lazy eval
            sexpr_t arg_val;
            eval(&arg_val, CAR(next_arg), env);
            env_put(&new_env, SYMBOL(CAR(next_par)), arg_val);
        }

        next_par = CDR(next_par);
        next_arg = CDR(next_arg);
    }
    env_put(&new_env, SYM_SELF, *lambda); // TODO avoid parameter named self

    eval(out, body, &new_env);
}

/* example  ((lambda (x) (+ x 1)) 2)*/
void eval_lambda_call (sexpr_t* out, sexpr_t* in, env_t* env) {
    eval_function_call(out, CAR(in), CDR(in), env);
}

void eval_sym_call (sexpr_t* out, sexpr_t* in, env_t* env) {
    sexpr_t* lambda = env_get(env, SYMBOL(CAR(in)));

    if (lambda != NULL) {
        eval_function_call(out, lambda, CDR(in), env);
    } else {
        // error
    }
}

void eval_def (sexpr_t* out, sexpr_t* in, env_t* env) {
    sexpr_t* name = CADR(in);
    sexpr_t* expr = CAR(CDDR(in)); // TODO: check errors
    sexpr_t val;

    eval(&val, expr, env);

    env_put(env, SYMBOL(name), val);

    *out = val;
}

void eval (sexpr_t* out, sexpr_t* in, env_t* env) {
    sexpr_t aux;

    if (IS_ATOM(in)) {
        if (IS_SYMBOL(in)) {
            *out = *(env_get(env, SYMBOL(in)));
        } else {
            *out = *in;
        }
    } else if (IS_CONS(in)) {
        sexpr_t car_val;

        if (IS_CONS(CAR(in))) {
            eval(&car_val, CAR(in), env);
        } else {
            car_val = *(CAR(in));
        }

        if (IS_ATOM(&car_val)) {
            if (IS_SYMBOL(&car_val)) {
                switch (SYMBOL(&car_val)) {
                    case SYM_QUOTE: *out = *(CADR(in)); break; //check that cdr is a cons!
                    case SYM_PLUS: eval_plus(out, in, env); break;
                    case SYM_MINUS: eval_minus(out, in, env); break;
                    case SYM_TIMES: eval_times(out, in, env); break;
                    case SYM_IF: eval_if(out, in, env); break;
                    case SYM_EQ: eval_eq(out, in, env); break;
                    case SYM_EVAL: eval(&aux, CADR(in), env); eval(out, &aux, env); break;
                    case SYM_CONS: eval_cons(out, in, env); break;
                    case SYM_CAR:  eval(&aux, CADR(in), env); *out = *(CAR(&aux)); break; // check
                    case SYM_CDR:  eval(&aux, CADR(in), env); *out = *(CDR(&aux)); break; // check
                    case SYM_LAMBDA: *out = *in; break;
                    case SYM_DEF: eval_def(out, in, env); break;
                    default: eval_sym_call(out, in, env); break;
                }   
            } else {
                // error;
            }
        } else if (IS_CONS(&car_val)) {
            if (IS_SYMBOL(CAR(&car_val)) && SYMBOL(CAR(&car_val)) == SYM_LAMBDA) {
                eval_lambda_call(out, in, env);
            } else {
                // error
            }
        } else {
            // error;
        }
    } else {
        // error; 
    }
}