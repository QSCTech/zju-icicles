#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int a, i, n, sum;
    int ri, looptimes;

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        a = GetInteger();
        n = GetInteger();
        sum = 1;
        for (i = 0; i <= n; ++i) {
            sum *= 10;
        }
        sum /= 9;
        sum -= n + 1;
        sum = sum / 9 * a;
        printf("sum = %d\n", sum);
    }
    return 0;
}
