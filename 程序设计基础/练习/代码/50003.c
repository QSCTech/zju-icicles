#include <stdio.h>

int main(void)
{
    int flag, i, n;
    int looptimes, ri;
    double item, sum;

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%d", &n);
        sum = 0;
        n = 3 * n;
        for (i = 1; i <= n; i += 3) {
            sum += (i % 2 * 2 - 1) / (double) i;
        }
        printf("sum = %.3f\n", sum);
    }

    return 0;
}
