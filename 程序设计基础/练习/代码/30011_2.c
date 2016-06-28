#include <stdio.h>
#include <math.h>
#include "genlib.h"

int main(void)
{
    int rep,ri;
    double x, y;

    rep = GetInteger();
    for (ri = 1; ri <= rep; ++ri) {
        x = GetReal();
        y = x >= 0 ? sqrt(x) : (pow(x + 1, 2) + 2 * x + 1 / x);
        printf("f(%.2f) = %.2f\n", x, y);
    }
    return 0;
}
