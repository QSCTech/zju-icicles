#include <stdio.h>

int main(void)
{
    int i, n;
    int looptimes, ri;
    double deno, num, sum, temp;

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%d", &n);
        sum = 0;
        num = 2;
        deno = 1;
        for (i = 0; i < n; ++i) {
            sum += num / deno;
            temp = num;
            num = num + deno;
            deno = temp;
        }
        printf("sum = %.2f\n",sum);
    }

    return 0;
}
