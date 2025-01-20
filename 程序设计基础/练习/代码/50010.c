#include <stdio.h>
#include <math.h>

int main(void)
{
    int looptimes, ri;
    double a, b, c, delta;

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%lf%lf%lf", &a, &b, &c);
        if (a == 0 && b == 0) {
            if (c == 0) {
                printf("������Ϊ�㣬����������!\n");
            } else {
                printf("a��bΪ0��c��Ϊ0�����̲�����\n");
            }
        } else {
            if (a == 0) {
                printf("x = %0.2f\n", - c / b);
            } else {
                delta = b * b - 4 * a * c;
                if (delta > 0) {
                    printf("x1 = %0.2f\n", (- b + sqrt(delta)) / (2 * a));
                    printf("x2 = %0.2f\n", (- b - sqrt(delta)) / (2 * a));
                } else {
                    printf("x1 = %0.2f+%0.2fi\n", - b / (2 * a), sqrt(- delta) / (2 * a));
                    printf("x2 = %0.2f-%0.2fi\n", - b / (2 * a), sqrt(- delta) / (2 * a));
                }
            }
        }
    }

    return 0;
}
