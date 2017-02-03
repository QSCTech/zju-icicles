%{
#include <stdio.h>
#include "5-30.y.h"
%}

%option noyywrap

%%

[0-9]+ {
    yylval.value_type = TYPE_INTEGER;
    yylval.integer_value = atoi(yytext);
    return NUMBER;
}

([0-9]*("."[0-9]+)?) {
    yylval.value_type = TYPE_FLOAT;
    yylval.float_value = atof(yytext);
    return NUMBER;
}

[^ \t\n] {
    return yytext[0];
}

\n {
    return 0;
}

. {}

%%
