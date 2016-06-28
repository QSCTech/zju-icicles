#include <stdio.h>

int main(void)
{
    int i, n;
    int looptimes, ri;
    double sum;

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%d", &n);
        n = 2 * n;
        sum = 0;
        for (i = 1; i < n; i += 2) {
            sum += 1.0 / i;
        }
        printf("sum = %.6f\n", sum);
    }

    return 0;
}
