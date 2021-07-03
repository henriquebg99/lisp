%option noyywrap
%{
#define YY_DECL int yylex(symbols_t* symbols)
#include <string.h>
#include <stdio.h>
#include "sexpr.h"
#include "y.tab.h"
%}

dig [0-9]
let [a-zA-Z]
ext [-=+*/%^{};><!?]
%%
({let}|{ext})({let}|{ext}|{dig})*           { yylval.i = getsym(symbols, yytext); return tSYMBOL; }
[-+]?[0-9]+                                 { yylval.i = atoi(yytext); return tINTEGER; }
[-+]?[0-9]*[.][0-9]+                        { yylval.d = atof(yytext); return tDOUBLE; }
[()]                                        { return *yytext; }
[\t ]                                       ;
[\n]                                        { return *yytext; }
.                                           { fprintf(stderr, "Error: %c no recognized", *yytext);}
%%