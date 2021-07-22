#include "sexpr.h"
#include <stdlib.h>

/* optimization */
sexpr_t nil = {.type = S_ATOM, .atom = {.type = A_NIL}};
sexpr_t t = {.type = S_ATOM, .atom = {.type = A_BOOL, .b = 1}};
sexpr_t f = {.type = S_ATOM, .atom = {.type = A_BOOL, .b = 0}};

sexpr_t* sexpr_alloc () {
    return malloc (sizeof(sexpr_t));
}