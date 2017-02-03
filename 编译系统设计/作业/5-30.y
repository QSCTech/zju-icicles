%{
#include <stdio.h>
#include <ctype.h>
%}

%code requires {
typedef enum {
    TYPE_INTEGER,
    TYPE_FLOAT
} value_type_t;

typedef struct {
    int integer_value;
    float float_value;
    value_type_t value_type;
} type;

#define YYLTYPE type
#define YYSTYPE type
}

%token NUMBER

%%

command : exp {
    if ($1.value_type == TYPE_INTEGER) {
        printf("%d\n", $1.integer_value);
    } else {
        printf("%f\n", $1.float_value);
    }
}
        ; /* allows printing of the result */

exp : exp '+' term {
    if ($1.value_type == TYPE_INTEGER && $3.value_type == TYPE_INTEGER) {
        $$.value_type = TYPE_INTEGER;
        $$.integer_value = $1.integer_value + $3.integer_value;
    } else if ($1.value_type == TYPE_INTEGER) {
        $$.value_type = TYPE_FLOAT;
        $$.float_value = $1.integer_value + $3.float_value;
    } else if ($3.value_type == TYPE_INTEGER) {
        $$.value_type = TYPE_FLOAT;
        $$.float_value = $1.float_value + $3.integer_value;
    } else {
        $$.value_type = TYPE_FLOAT;
        $$.float_value = $1.float_value + $3.float_value;
    }
}
    | exp '-' term {
    if ($1.value_type == TYPE_INTEGER && $3.value_type == TYPE_INTEGER) {
        $$.value_type = TYPE_INTEGER;
        $$.integer_value = $1.integer_value - $3.integer_value;
    } else if ($1.value_type == TYPE_INTEGER) {
        $$.value_type = TYPE_FLOAT;
        $$.float_value = $1.integer_value - $3.float_value;
    } else if ($3.value_type == TYPE_INTEGER) {
        $$.value_type = TYPE_FLOAT;
        $$.float_value = $1.float_value - $3.integer_value;
    } else {
        $$.value_type = TYPE_FLOAT;
        $$.float_value = $1.float_value - $3.float_value;
    }
}
    | term { $$ = $1; }
    ;

term : term '*' factor {
    if ($1.value_type == TYPE_INTEGER && $3.value_type == TYPE_INTEGER) {
        $$.value_type = TYPE_INTEGER;
        $$.integer_value = $1.integer_value * $3.integer_value;
    } else if ($1.value_type == TYPE_INTEGER) {
        $$.value_type = TYPE_FLOAT;
        $$.float_value = $1.integer_value * $3.float_value;
    } else if ($3.value_type == TYPE_INTEGER) {
        $$.value_type = TYPE_FLOAT;
        $$.float_value = $1.float_value * $3.integer_value;
    } else {
        $$.value_type = TYPE_FLOAT;
        $$.float_value = $1.float_value * $3.float_value;
    }
}
     | term '/' factor {
    if ($1.value_type == TYPE_INTEGER && $3.value_type == TYPE_INTEGER) {
        $$.value_type = TYPE_INTEGER;
        $$.integer_value = $1.integer_value / $3.integer_value;
    } else if ($1.value_type == TYPE_INTEGER) {
        $$.value_type = TYPE_FLOAT;
        $$.float_value = $1.integer_value / $3.float_value;
    } else if ($3.value_type == TYPE_INTEGER) {
        $$.value_type = TYPE_FLOAT;
        $$.float_value = $1.float_value / $3.integer_value;
    } else {
        $$.value_type = TYPE_FLOAT;
        $$.float_value = $1.float_value / $3.float_value;
    }
}
     | factor { $$ = $1; }
     ;

factor : NUMBER { $$ = $1; }
       | '(' exp ')' { $$ = $2; }
       ;

%%

int main() {
    return yyparse();
}

/* allows for printing of an error message */
int yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
    return 0;
}
