#include "stdio.h"
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int i, j, n, o, p, q, r;
    int looptimes, ri;

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        n = GetInteger();
        /* Print lines */
        o = 2 * n;
        /* i is line number */
        for (i = 1; i != o; ++i) {
            /* Print leading spaces */
            p = 2 * (n - i);
            if (p < 0) { p = -p; }
            for (j = 0; j != p; ++j) { printf(" "); }
            /* Print asterisks and spaces between */
            q = 2 * i - 1;
            r = 2 * n - 1;
            if (q > r) { q = 2 * r - q; } 
            for (j = 0; j != q; ++j) {
                if (j != 0) { printf(" "); }
                printf("*");
            }
            /* Print new line */
            printf("\n");
        }
    }
    return 0;
}
