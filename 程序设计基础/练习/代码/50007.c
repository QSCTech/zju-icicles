#include <stdio.h>

int main(void)
{
    int flag, i, n;
    int looptimes, ri;
    double item, sum;

    scanf("%d", &looptimes);
    for(ri = 1; ri <= looptimes; ++ri) {
        scanf("%d", &n);
        sum = 1;
        n += 1;
        for (i = 2; i < n; ++i) {
            sum += (i % 2 * 2 - 1.0) * i / (2 * i - 1);
        }
        printf("sum = %.3f\n", sum);
    }

    return 0;
}
