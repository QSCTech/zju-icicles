#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int m, sum[] = {1, 3, 9, 33, 153, 873, 5913, 46233, 409113};
    m = GetInteger();

    printf("1!+2!+...+%d! = %f\n", m, (double) sum[m - 1]);
    return 0;
}
