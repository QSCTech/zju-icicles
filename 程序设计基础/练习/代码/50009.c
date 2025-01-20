#include <stdio.h>

int main(void)
{
    int i, n, t;
    int looptimes, ri;
    double sum;

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%d", &n);
        sum = 2;
        t = 1;
        for (i = 2; i <=n; ++i) {
            t *= i;
            sum += t;
        }
        printf("sum = %.0f\n", sum);
    }

    return 0;
}
