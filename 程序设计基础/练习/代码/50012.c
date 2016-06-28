#include <stdio.h>
#include <math.h>

int main(void)
{
    int d, flag;
    int looptimes, ri;
    double eps, item, sum;

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%le", &eps);
        sum = 0;
        d = 1;
        while ((item = 1.0 / d) >= eps) {
            item *= d % 2 * 2 - 1;
            sum += item;
            d += 3;
        }
        item *= d % 2 * 2 - 1;
        sum += item;
        printf("sum = %.6f\n", sum);
   }

   return 0;
}
