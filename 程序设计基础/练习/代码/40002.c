#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int sign(int x);

int main(void)
{
    int x, y;
    int looptimes, ri;

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        x = GetInteger();
        y = sign(x);
        printf("sign(%d) = %d\n", x, y);
    }
    return 0;
}

int sign(int x) {
    return x > 0 ? 1 : (x == 0 ? 0 : -1);
}
