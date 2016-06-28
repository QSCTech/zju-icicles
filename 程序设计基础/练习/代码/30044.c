#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int looptimes, ri;
    int year;

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        year = GetInteger();
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        {
            printf("%d is a leap year.\n",year);
        } else {
            printf("%d isn't a leap year.\n",year);
        }
    }
    return 0;
}
