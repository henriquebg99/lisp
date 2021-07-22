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
    env_t env;
    env_init(&env, NULL);
    env_put(&env, SYM_NIL, nil);
    env_put(&env, SYM_T, t);
    env_put(&env, SYM_F, f);

    eval(&res, exp, &env);

    print(&symbols, &res);
    printf("\n");

    //freesymbols(&symbols);

    return 0;
}