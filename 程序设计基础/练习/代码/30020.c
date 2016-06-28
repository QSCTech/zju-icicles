#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int i, m, sum;
    int looptimes, ri;

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        m = GetInteger();
        sum = (m + 100) * (101 - m) / 2;
        printf("sum = %d\n", sum);
    }
    return 0;
}
