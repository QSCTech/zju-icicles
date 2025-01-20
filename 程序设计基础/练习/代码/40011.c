#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int a, i, n;
    int ri, looptimes;
    long an, sn;

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        a = GetInteger();
        n = GetInteger();
        sn = a;
        an = 10;
        for (i = 1; i < n; ++i) {
            an *= 10;
            sn += (an - 1) / 9 * a;
        }
        printf("%ld\n", sn);
    }
    return 0;
}
