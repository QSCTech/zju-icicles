#include <stdio.h>

int main(void)
{
    int i, m, n;
    int looptimes, ri;
    double sum;

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%d %d", &m, &n);
        sum = 0;
        for (i = m; i <= n; ++i) {
            sum += 1.0 / i;
        }
        printf("sum = %.3f\n", sum);
    }
    return 0;
}
