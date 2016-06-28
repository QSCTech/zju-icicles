#include <stdio.h>
#include <math.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int money, year;
    double interest, rate;

    money = GetInteger();
    year = GetInteger();
    rate = GetReal();
    interest = money * pow(1 + rate, year) - money;
    printf("interest = %.2f\n", interest);
    return 0;
}
