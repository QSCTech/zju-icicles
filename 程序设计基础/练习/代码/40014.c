#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    long in, res;
    int ri, looptimes;
    long reverse(long number);

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        in = GetInteger();
        res = reverse(in);
        printf("%ld\n", res);
    }
    return 0;
}

long reverse(long number) {
    long result = 0;
    int negative = 0;
    if (number < 0) {
        number = -number;
        negative = 1;
    }
    while (number > 0) {
        result *= 10;
        result += number % 10;
        number /= 10;
    }
    if (negative) {
        result = -result;
    }
    return result;
}
