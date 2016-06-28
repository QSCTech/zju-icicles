#include "stdio.h"
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int i, m, n;
    int looptimes, ri;
    int is_narcissistic_number(int number);

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
         m = GetInteger();
         n = GetInteger();
        printf("result:\n");
        for (i = m; i <= n; ++i) {
            if (is_narcissistic_number(i)) {
                printf("%d\n", i);
            }
        }
    }
    return 0;
}

int is_narcissistic_number(int number) {
    int sum, n, m;
    n = number;
    sum = 0;
    while (n != 0) {
        m = n % 10;
        sum += m * m * m;
        n /= 10;
    }
    return sum == number;
}
