#include <stdio.h>
#include <stdlib.h>

typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

ElementType EvalPostfix( char *expr );

int main()
{
    ElementType v;
    char expr[Max_Expr];
    gets(expr);
    v = EvalPostfix( expr );
    if ( v < Infinity )
        printf("%f\n", v);
    else
        printf("ERROR\n");
    return 0;
}


ElementType EvalPostfix( char *expr ) {
    char t[10];
    double s[100],flag;
    int c = 0,k = 0;
    while(expr[k]) {
        int j = 0;
        while(expr[k] && expr[k] != ' ') t[j ++] = expr[k ++];
        t[j] = 0;
        if(t[0] >= '0' && t[0] <= '9' || t[1] && (t[0] == '-' || t[0] == '+')) {
            s[c] = 0;
            int i = 0;
            flag = 1;
            if(t[i] == '-') {
                flag = -1;
                i ++;
            }
            if(t[i] == '+') i ++;
            while(t[i] && t[i] != '.') {
                s[c] = s[c] * 10 + t[i ++] - '0';
            }
            if(t[i] == '.') {
                i ++;
                double d = 0.1;
                while(t[i]) {
                    s[c] += (t[i ++] - '0') * d;
                    d *= 0.1;
                }
            }
            s[c] *= flag;
            c ++;
        }
        else {
            if(c < 2) return Infinity;
            switch(t[0]) {
                case '+':s[c - 2] += s[c - 1];break;
                case '-':s[c - 2] -= s[c - 1];break;
                case '*':s[c - 2] *= s[c - 1];break;
                case '/': if(s[c - 1] == 0) return Infinity;
                          s[c - 2] /= s[c - 1];break;
            }
            c --;
        }
        while(expr[k] && expr[k] == ' ') k ++;
    }
    if(c > 1) return Infinity;
    return s[0];
}
