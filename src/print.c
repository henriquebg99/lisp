#include "print.h"
#include <stdio.h>

void print (symbols_t* symbols, sexpr_t* e) {
    if (IS_ATOM(e)) {
        switch (e->atom.type) {
        case A_INTEGER: printf("%d", e->atom.i); break;
        case A_DOUBLE: printf("%f", e->atom.d); break;
        case A_STRING: printf("%s", e->atom.str); break;
        case A_SYMBOL: printf("%s", getname(symbols, e->atom.sym)); break;
        case A_BOOL: printf("%s", IS_TRUE(e) ? "t" : "f"); break;
        default: break;
        }
    } else if (IS_CONS(e)) {
        printf("(");

        sexpr_t *next = e;
        while (IS_CONS(next) && IS_CONS(CDR(next))) {
            print(symbols, CAR(next));
            printf(" ");
            next = CDR(next);
        }

        print(symbols, CAR(next));

        if (!IS_NIL(CDR(next))) {
            printf(" . ");
            print(symbols, CDR(next));
        }

        printf(")");
    } else {
        // error
    }
}