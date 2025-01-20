#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

double fact(int n);
double multi(int n);

int main(void)
{
    int i;
    int looptimes, ri;
    double eps, sum, item;

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        eps = GetReal();
        i = 0;
        sum = 0;
        while ((item = fact(i) / multi(2 * i + 1)) >= eps) {
            sum += item;
            ++i;
        }
        sum += item;
        printf("PI = %0.5f\n", 2 * sum);
    }

    return 0;
}

double fact(int n) {
    return n == 0 || n == 1 ? 1 : n * fact(n - 1);
}

double multi(int n) {
    return n == 1 ? 1 : n * multi(n - 2);
}
