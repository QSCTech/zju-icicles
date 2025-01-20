#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void) {
    int ri, looptimes, n;
    
    void dectobin(int n);

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        n = GetInteger();
        dectobin(n);
        printf("\n");
    }
    return 0;
}
/* `(n >> k) & 1` returns the bit at the kth location, however we will have to deal with big/little endian. */
void dectobin(int n) {
    long bin = 0, base = 1;
    while (n != 0) {
        bin += n % 2 * base;
        n /= 2;
        base *= 10;
    }
    printf("%ld", bin);
}
