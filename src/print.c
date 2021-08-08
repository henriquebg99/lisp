#include "print.h"
#include <stdio.h>

void print (symbols_t* symbols, sexpr_t* e) {
    if (IS_ATOM(e)) {
        switch (e->type) {
        case S_INTEGER: printf("%d", INTEGER(e)); break;
        case S_DOUBLE: printf("%f", DOUBLE(e)); break;
        case S_STRING: printf("%s", STRING(e)); break;
        case S_SYMBOL: printf("%s", getname(symbols, SYMBOL(e))); break;
        case S_BOOL: printf("%s", IS_TRUE(e) ? "t" : "f"); break;
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