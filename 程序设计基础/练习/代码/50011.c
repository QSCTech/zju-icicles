#include <stdio.h>

int main(void)
{
    int gcd, lcm, m, n, p, q;
    int looptimes, ri;

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%d", &m);
        scanf("%d", &n);
        if (m <= 0 || n <= 0)
            printf("m <= 0 or n <= 0");
        else{
            lcm = m * n;
            if (m > n) {
                p = m;
                q = n;
            } else {
                p = n;
                q = m;
            }
            gcd = q;
            while (p % q != 0) {
                gcd = p % q;
                q = p;
                p = gcd;
            }
            lcm /= gcd;
            printf("%d is the least common multiple of %d and %d, %d is the greatest common divisor of %d and %d.\n", lcm, m, n, gcd, m, n);
        }
    }

    return 0;
}
