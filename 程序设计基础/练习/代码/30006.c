#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int a, b, c;
    double average;

    a = GetInteger();
    b = GetInteger();
    c = GetInteger();
    average = (a + b + c) / 3.0;
    printf("average = %.2f\n", average);
    return 0;
}
