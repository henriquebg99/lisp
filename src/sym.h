#ifndef SYM_H
#define SYM_H

#define INIT_ENTRIES 8

/* the symbol data type */
typedef int sym_t;

/* dynamic array to store all the symbols */
typedef struct {
    char** array;
    int total, used;
} symbols_t;

/* existing symbols */
#define SYM_QUOTE 0
#define SYM_EVAL 1
#define SYM_IF 2
#define SYM_PLUS 3

void initsymbols (symbols_t* symbols);
sym_t getsym (symbols_t* symbols, const char* string);
const char* getname (symbols_t* symbols, sym_t sym);
void freesymbols (symbols_t* symbols);

#endif