#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int looptimes, ri;
    double x, y;

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        x = GetReal();
        y = x != 10 ? x : 1 / x;
        printf("f(%.1f) = %.1f\n", x, y);
    }
    return 0;
}
