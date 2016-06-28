#include <stdio.h>
#include <math.h>

int main(void)
{
    int i,n;
    int looptimes, ri;
    double sum;

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%d", &n);
        sum = pow(2, n + 1) - 2;
        printf("sum = %.0f\n", sum);
    }

    return 0;
}
