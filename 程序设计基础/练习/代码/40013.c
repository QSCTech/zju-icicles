#include "stdio.h"
#include "math.h"
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int i, m, n, first;
    int looptimes, ri;
    int factorsum(int number);

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        m = GetInteger();
        n = GetInteger();
        first = 1;
        for (i = m; i <= n; ++i) {
            if (factorsum(i) == i) {
                if (first) {
                    first =0;
                } else {
                    printf(" ");
                }
                printf("%d", i);
            }
        }
        printf("\n");
    }
    return 0;
}

int factorsum(int number) {
    int i, sum;
    double limit;
    if (number == 1) {
        return 1;
    } else {
        sum = 1;
        limit = sqrt(number);
        for (i = 2; i < limit; ++i) {
            if (number % i == 0) {
                sum = sum + i + number / i;
            }
        }
        if (i == limit) {
            sum += i;
        }
        return sum;
    }
}
