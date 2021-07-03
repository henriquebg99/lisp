#include "print.h"
#include <stdio.h>

void print (symbols_t* symbols, sexpr_t* e) {
    if (e->type == S_ATOM) {
        switch (e->atom.type) {
        case A_INTEGER: printf("%d", e->atom.i); break;
        case A_SYMBOL: printf("%s", getname(symbols, e->atom.sym)); break;
        default: break;
        }
    } else if (e->type == S_CONS) {
        printf("(");

        if (!IS_NIL(e)) {
            sexpr_t *next = e;
            while (!IS_NIL(CDR(next))) {
                print(symbols, CAR(next));
                printf(" ");
                next = CDR(next);
            }

            print(symbols, CAR(next));
        }

        printf(")");
    } else {
        // error
    }
}