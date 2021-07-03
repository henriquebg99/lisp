#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "sexpr.h"
#include "y.tab.h"
#include "eval.h"
#include "print.h"

int main () {
    sexpr_t* exp;
    symbols_t symbols;

    initsymbols(&symbols);

    yyparse(&symbols, &exp);

    sexpr_t res;
    eval(&res, exp);

    print(&symbols, &res);
    printf("\n");

    //freesymbols(&symbols);

    return 0;
}