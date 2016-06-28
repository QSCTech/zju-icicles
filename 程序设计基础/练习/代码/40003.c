#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int even(int n);

int main(void)
{
    int n, sum;
    int ri, looptimes;

   looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        sum = 0;
        while ((n = GetInteger()) > 0) {
            if (!even(n)) {
                sum += n;
            }
        }
        printf("The sum of the odd numbers is %d.\n", sum);
   }
}

int even(int n) {
     return n - n / 2 * 2 == 0;
}
