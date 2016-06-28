#include "stdio.h"
#include "math.h"
#include "genlib.h"
#include "simpio.h"

int main(void)
{
   int i, m, n;
   int looptimes, ri, first;
   long f;
   long fib(int n);

   looptimes = GetInteger();
   for (ri = 1; ri <= looptimes; ++ri) {
        m = GetInteger();
        n = GetInteger();
        i = 1;
        first = 1;
        while (1) {
            long f = fib(i);
            if (f >= m) {
                if (f > n) {
                    break;
                } else {
                    if (first) {
                        first = 0;
                    } else {
                        printf(" ");
                    }
                    printf("%ld", f);
                }
            }
            ++i;
        }
        printf("\n");
    }
    return 0;
}

long fib(int n) {
    return n == 1 || n == 2 ? 1 : fib(n - 1) + fib(n - 2);
}
