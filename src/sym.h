#ifndef SYM_H
#define SYM_H

#define INIT_ENTRIES 32

/* the symbol data type */
typedef int sym_t;

/* dynamic array to store all the symbols */
typedef struct {
    char** array;
    int total, used;
} symbols_t;

/* existing symbols */
enum base_symbols {
    SYM_QUOTE, SYM_EVAL, SYM_IF, SYM_PLUS, SYM_CONS, SYM_CAR, SYM_CDR, SYM_LAMBDA, SYM_NIL
};

void initsymbols (symbols_t* symbols);
sym_t getsym (symbols_t* symbols, const char* string);
const char* getname (symbols_t* symbols, sym_t sym);
void freesymbols (symbols_t* symbols);

#endif