#include "eval.h"

void eval_plus (sexpr_t* out, sexpr_t* in) {
    sexpr_t *arg1 = CAR(CDR(in)), *arg2;
    sexpr_t v1, v2;

    if (IS_CONS(CDR(CDR(in)))) {
        arg2 = CAR(CDR(CDR(in)));
    } else {
        // error
    }

    eval(&v1, arg1);
    eval(&v2, arg2);

    out->type = S_ATOM;
    out->atom.type = A_INTEGER;
    out->atom.i = INTEGER(&v1) + INTEGER(&v2);
}

void eval (sexpr_t* out, sexpr_t* in) {
    if (in->type == S_ATOM) {
        *out = *in;
    } else {
        if (IS_SYMBOL(CAR(in))) {
            switch (CAR(in)->atom.sym) {
                case SYM_QUOTE: *out = *(CAR(CDR(in))); break;
                case SYM_PLUS: eval_plus(out, in); break;
            }
        }
    }
}