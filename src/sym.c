#include "sym.h"
#include <stdlib.h>
#include <string.h>

void initsymbols (symbols_t* symbols) {
    symbols->array = (char **) malloc (INIT_ENTRIES * sizeof(char*));
    symbols->total = INIT_ENTRIES;

    symbols->array[SYM_QUOTE] = "quote";
    symbols->array[SYM_EVAL] = "eval";
    symbols->array[SYM_IF] = "if";
    symbols->array[SYM_PLUS] = "+";
    symbols->array[SYM_MINUS] = "-";
    symbols->array[SYM_EQ] = "=";
    symbols->array[SYM_CONS] = "cons";
    symbols->array[SYM_CAR] = "car";
    symbols->array[SYM_CDR] = "cdr";
    symbols->array[SYM_LAMBDA] = "lambda";
    symbols->array[SYM_NIL] = "nil";
    symbols->array[SYM_SELF] = "self";
    symbols->array[SYM_T] = "t";
    symbols->array[SYM_F] = "f";
    symbols->array[SYM_TIMES] = "*";
    symbols->array[SYM_DEF] = "def";
    
    symbols->used  = 16;
}

sym_t getsym (symbols_t* symbols, const char* string) {
    /* search if already used */
    for (int i = 0; i < symbols->used; i++) {
        if (strcmp(string, symbols->array[i]) == 0) {
            return i;
        }
    }

    if (symbols->total == symbols->used) { /* not enough space */
        symbols->array = realloc(symbols->array, 2 * symbols->total * sizeof(char*));
        symbols->total *= 2;
    }

    /* add */
    symbols->array[symbols->used] = strdup(string);

    return symbols->used++;
}

const char* getname (symbols_t* symbols, sym_t sym) {
    return symbols->array[sym];
}

void freesymbols (symbols_t* symbols) {
    for (int i = 0; i < symbols->used; i++) {
        free(symbols->array[i]);
    }

    free(symbols->array);
}