#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int a, b, maximum;
    int looptimes, ri;

    looptimes = GetInteger();

    for (ri = 1; ri <= looptimes; ++ri) {
        a = GetInteger();
        b = GetInteger();
        maximum = a >= b ? a : b;
        printf("max(%d,%d) = %d\n", a, b, maximum);
    }
    return 0;
}
