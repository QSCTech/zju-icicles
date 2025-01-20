#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int n;
    double factorial;
    double fact(int n);

    n = GetInteger();
    factorial = fact(n);
    printf("%d! = %f\n", n, factorial);
    return 0;
}

double fact(int n) {
    double f = 1;
    int i;
    for (i = 2; i <= n; ++i) {
        f *= i;
    }
    return f;
}
