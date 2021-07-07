#include "eval.h"

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

/* example  ((lambda (x) (+ x 1)) 2)*/
void eval_lambda_call (sexpr_t* out, sexpr_t* in, env_t* env) {
    sexpr_t *lambda = CAR(in);
    sexpr_t *params = CADR(lambda);
    sexpr_t *args = CDR(in);
    sexpr_t *body = CAR(CDR(CDR(CAR(in))));

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

    eval(out, body, &new_env);
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
                    case SYM_EVAL: eval(&aux, CADR(in), env); eval(out, &aux, env); break;
                    case SYM_CONS: eval_cons(out, in, env); break;
                    case SYM_CAR:  eval(&aux, CADR(in), env); *out = *(CAR(&aux)); break; // check
                    case SYM_CDR:  eval(&aux, CADR(in), env); *out = *(CDR(&aux)); break; // check
                    case SYM_LAMBDA: *out = *in; break;
                    default: break;
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