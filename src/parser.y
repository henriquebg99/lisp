%{
#include <stdio.h>
#include "sexpr.h"

extern int yylex();
void yyerror(symbols_t* symbols, sexpr_t** retval, const char* message) {
    fprintf(stderr, "%s", message);
}
%}

%parse-param {symbols_t* symbols}
%parse-param {sexpr_t** retval}
%lex-param {symbols}
%union { 
    int i; 
    double d;
    sexpr_t* e;
}

%token<i> tINTEGER
%token<i> tSYMBOL
%token<d> tDOUBLE
%type<e> sexpr
%type<e> atom
%type<e> list
%type<e> start

%start start
%%

start   : sexpr '\n'            {{ *retval = $1; }}

sexpr   : atom              {{ $$ = $1; }}
        | '(' list ')'      {{ $$ = $2; }}
        ;

atom    : tINTEGER          {{ $$ = sexpr_alloc(); $$->type = S_ATOM; $$->atom.type = A_INTEGER; $$->atom.i = $1; }}
        | tSYMBOL           {{ $$ = sexpr_alloc(); $$->type = S_ATOM; $$->atom.type = A_SYMBOL;  $$->atom.sym = $1; }}
        | tDOUBLE           {{ $$ = sexpr_alloc(); $$->type = S_ATOM; $$->atom.type = A_DOUBLE;  $$->atom.d = $1; }}
        ;

list    : sexpr list        {{ $$ = sexpr_alloc(); $$->type = S_CONS; $$->cons.car = $1; $$->cons.cdr = $2; }}
        |                   {{ $$ = &nil; }}
%%