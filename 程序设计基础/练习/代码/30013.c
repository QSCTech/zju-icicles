#include <stdio.h>
#include <genlib.h>
#include "simpio.h"

int main(void)
{
    int looptimes, ri;
    int x, y;

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        x = GetInteger();
        y = x < 0 ? -1 : (x == 0 ? 0 : 1);
        printf("sign(%d) = %d\n", x, y);
    }
    return 0;
}
