#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int n;
    int looptimes, ri;
    void pyramid(int n);

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        n=GetInteger();
        pyramid(n);
    }
    return 0;
}

void pyramid(int n) {
    int i, j, k;
    for (i = 1; i <= n; ++i) {
        /* Print leading spaces */
        k = n - i;
        for (j = 0; j < k; ++j) {
            printf(" ");
        }
        /* Print numbers and spaces between */
        for (j = 0; j < i; ++j) {
            if (j != 0) {
                printf(" ");
            }
            printf("%d", i);
        }
        /* Print new line */
        printf("\n");
    }
}
