%{
#include <stdio.h>

size_t char_count = 0, word_count = 0, line_count = 0;
%}

%option noyywrap

%%

\n {
    ++char_count;
    ++line_count;
}

[^ \t\n]+ {
    char_count += yyleng;
    ++word_count;
}

. {
    ++char_count;
}

%%

int main() {
    yylex();
    printf("%d\t%d\t%d\n", char_count, word_count, line_count);
    return 0;
}
