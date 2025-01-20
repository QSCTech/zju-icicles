#include <stdio.h>
#include "genlib.h"
#include "simpio.h"
int main(void)
{
    int i, min, n, x;
    int looptimes, ri;

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        n = GetInteger();
        min = GetInteger();
        for (i = 1; i < n; ++i) {
            x = GetInteger();
            if (x < min) {
                min = x;
            }
        }
        printf("min = %d\n", min);
    }
    return 0;
}
