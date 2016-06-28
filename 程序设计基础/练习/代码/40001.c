#include "stdio.h"
#include "genlib.h"
#include "simpio.h"

double fact(int n);

int main(void)
{
    int m, n;
    int looptimes, ri;
    double s;

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        m = GetInteger();
        n = GetInteger();
        s = fact(n) / fact(m) / fact(n - m);
        printf("result = %.0f\n", s);
    }
    return 0;
}

double fact(int n) {
    return n == 0 || n == 1 ? 1 : n * fact(n - 1);
}
