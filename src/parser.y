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
    char* str;
    sexpr_t* e;
}

%token tEND_OF_FILE
%token<i> tINTEGER
%token<i> tSYMBOL
%token<d> tDOUBLE
%token<str> tSTRING
%type<e> sexpr
%type<e> atom
%type<e> list
%type<e> start

%start start
%%

start   : sexpr             {{ *retval = $1; YYACCEPT;}}

sexpr   : atom              {{ $$ = $1; }}
        | '(' list ')'      {{ $$ = $2; }}
        ;

atom    : tINTEGER          {{ $$ = sexpr_alloc(); MK_INTEGER($$, $1);}}
        | tSYMBOL           {{ $$ = sexpr_alloc(); MK_SYMBOL($$, $1);}}
        | tDOUBLE           {{ $$ = sexpr_alloc(); MK_DOUBLE($$, $1);}}
        | tSTRING           {{ $$ = sexpr_alloc(); MK_STRING($$, $1);}}
        ;

list    : sexpr list        {{ $$ = sexpr_alloc(); MK_CONS($$, $1, $2);}}
        |                   {{ $$ = &nil; }}
%%