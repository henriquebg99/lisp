#ifndef SEXPR_H
#define SEXPR_H

#include "sym.h"

typedef struct sexpr_t sexpr_t;

/* cons */
typedef struct cons_t {
    sexpr_t *car, *cdr;
} cons_t;

/* atoms */
#define A_INTEGER 1
#define A_DOUBLE 2
#define A_SYMBOL 3
#define A_STRING 4
#define A_NIL 5
#define A_BOOL 6

typedef struct atom_t {
    int type;
    union {
        int i;
        double d;
        sym_t sym;
        const char* str;
        char b;
    };
} atom_t;

/* sexpr */
#define S_ATOM 1
#define S_CONS 2

struct sexpr_t {
    int type;
    union {
        atom_t atom;
        cons_t cons;
    };
};

/* optimization */
extern sexpr_t nil;
extern sexpr_t t;
extern sexpr_t f;

sexpr_t* sexpr_alloc ();

/* useful macros */
#define IS_ATOM(sexpr) ((sexpr)->type == S_ATOM)
#define IS_CONS(sexpr) ((sexpr)->type == S_CONS)
#define IS_SYMBOL(sexpr) ((sexpr)->type == S_ATOM && (sexpr)->atom.type == A_SYMBOL)
#define IS_INTEGER(sexpr) ((sexpr)->type == S_ATOM && (sexpr)->atom.type == A_INTEGER)
#define IS_DOUBLE(sexpr) ((sexpr)->type == S_ATOM && (sexpr)->atom.type == A_DOUBLE)
#define IS_STRING(sexpr) ((sexpr)->type == S_ATOM && (sexpr)->atom.type == A_STRING)
#define IS_BOOL(sexpr) ((sexpr)->type == S_ATOM && (sexpr)->atom.type == A_BOOL)
#define IS_NIL(sexpr) ((sexpr)->type == S_ATOM && (sexpr)->atom.type == A_NIL)

#define CAR(sexpr) ((sexpr)->cons.car)
#define CDR(sexpr) ((sexpr)->cons.cdr)
#define CADR(sexpr) (CAR(CDR((sexpr))))
#define CDDR(sexpr) (CDR(CDR(sexpr)))
#define INTEGER(sexpr) ((sexpr)->atom.i)
#define BOOL(sexpr) ((sexpr)->atom.b)
#define IS_TRUE(sexpr) ((sexpr)->atom.b == 1)
#define IS_FALSE(sexpr) ((sexpr)->atom.b == 0)
#define SYMBOL(sexpr) ((sexpr)->atom.sym)

#define MK_INTEGER(out, ival) {(out)->type = S_ATOM; (out)->atom.type = A_INTEGER; (out)->atom.i = (ival);}
#define MK_TRUE(out) {*out = t;}
#define MK_FALSE(out) {*out = f;}
#define MK_CONS(out, _car, _cdr) {(out)->type = S_CONS; (out)->cons.car = (_car); (out)->cons.cdr = (_cdr);}

#endif