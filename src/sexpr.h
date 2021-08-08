#ifndef SEXPR_H
#define SEXPR_H

#include "sym.h"

typedef struct sexpr_t sexpr_t;

#define S_INTEGER 1
#define S_DOUBLE 2
#define S_SYMBOL 3
#define S_STRING 4
#define S_NIL 5
#define S_BOOL 6
#define S_CONS 7


/* sexpr */

struct sexpr_t {
    int type;
    union {
        int i;
        double d;
        sym_t sym;
        const char* str;
        char b;
        struct {
            sexpr_t *car, *cdr;
        };
    };
};

/* optimization */
extern sexpr_t nil;
extern sexpr_t t;
extern sexpr_t f;

sexpr_t* sexpr_alloc ();

/* useful macros */
#define IS_ATOM(sexpr) ((sexpr)->type != S_CONS)
#define IS_CONS(sexpr) ((sexpr)->type == S_CONS)
#define IS_SYMBOL(sexpr) ((sexpr)->type == S_SYMBOL)
#define IS_INTEGER(sexpr) ((sexpr)->type == S_INTEGER)
#define IS_DOUBLE(sexpr) ((sexpr)->type == S_DOUBLE)
#define IS_STRING(sexpr) ((sexpr)->type == S_STRING)
#define IS_BOOL(sexpr) ((sexpr)->type == S_BOOL)
#define IS_NIL(sexpr) ((sexpr)->type == S_NIL)

#define CAR(sexpr) ((sexpr)->car)
#define CDR(sexpr) ((sexpr)->cdr)
#define CADR(sexpr) (CAR(CDR((sexpr))))
#define CDDR(sexpr) (CDR(CDR(sexpr)))
#define INTEGER(sexpr) ((sexpr)->i)
#define DOUBLE(sexpr) ((sexpr)->d)
#define BOOL(sexpr) ((sexpr)->b)
#define STRING(sexpr) ((sexpr)->str)
#define IS_TRUE(sexpr) ((sexpr)->b == 1)
#define IS_FALSE(sexpr) ((sexpr)->b == 0)
#define SYMBOL(sexpr) ((sexpr)->sym)

#define MK_INTEGER(out, ival) {(out)->type = S_INTEGER; (out)->i = (ival);}
#define MK_TRUE(out) {*(out) = t;}
#define MK_FALSE(out) {*(out) = f;}
#define MK_CONS(out, _car, _cdr) {(out)->type = S_CONS; (out)->car = (_car); (out)->cdr = (_cdr);}
#define MK_SYMBOL(out, symval) {(out)->type = S_SYMBOL; (out)->sym = (symval);}
#define MK_STRING(out, strval) {(out)->type = S_STRING; (out)->str = (strval);}
#define MK_DOUBLE(out, dval) {(out)->type = S_DOUBLE; (out)->d = (dval);}

#endif