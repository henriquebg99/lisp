#include "sexpr.h"
#include <stdlib.h>

/* optimization */
sexpr_t nil = {.type = S_ATOM, .atom = {.type = A_NIL}};

sexpr_t* sexpr_alloc () {
    return malloc (sizeof(sexpr_t));
}