#include "stdio.h"
#include "math.h"
#include "genlib.h"
#include "simpio.h"

double funcos(double e, double x);

int main(void)
{
    int looptimes, ri;
    double e, sum, x;

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        e = GetReal();
        x = GetReal();
        sum = funcos(e, x);
        printf("sum = %f\n", sum);
    }
    return 0;
}

/* Use double to avoid overflow */
double fact(double i) {
    return i == 0 || i == 1 ? 1 : i * fact(i - 1);
}

double funcos(double e, double x) {
    double sum = 1, item;
    int i = 2;
    while ((item = pow(x, (double) i) / fact((double) i)) >= e) {
        sum += (i / 4 * 4 - i + 1) * item;
        i += 2;
    }
    sum += (i / 4 * 4 - i + 1) * item;
    return sum;
}
