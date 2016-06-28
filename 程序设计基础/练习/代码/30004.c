#include <stdio.h>
#include "genlib.h"

int main(void)
{
    int celsius, fahr;

    fahr = GetInteger();
    celsius = 5 * (fahr - 32) / 9;
    printf("celsius = %d\n", celsius);
    return 0;
}
