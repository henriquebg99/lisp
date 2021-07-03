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

typedef struct atom_t {
    int type;
    union {
        int i;
        double d;
        sym_t sym;
        const char* str;
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

sexpr_t* sexpr_alloc ();

/* useful macros */
#define IS_ATOM(sexpr) ((sexpr)->type == S_ATOM)
#define IS_CONS(sexpr) ((sexpr)->type == S_CONS)
#define IS_SYMBOL(sexpr) ((sexpr)->type == S_ATOM && (sexpr)->atom.type == A_SYMBOL)
#define IS_INTEGER(sexpr) ((sexpr)->type == S_ATOM && (sexpr)->atom.type == A_INTEGER)
#define IS_DOUBLE(sexpr) ((sexpr)->type == S_ATOM && (sexpr)->atom.type == A_DOUBLE)
#define IS_STRING(sexpr) ((sexpr)->type == S_ATOM && (sexpr)->atom.type == A_STRING)
#define IS_NIL(sexpr) ((sexpr)->type == S_ATOM && (sexpr)->atom.type == A_NIL)
#define CAR(sexpr) ((sexpr)->cons.car)
#define CDR(sexpr) ((sexpr)->cons.cdr)
#define INTEGER(sexpr) ((sexpr)->atom.i)

#endif