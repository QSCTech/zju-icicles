#include <stdio.h>
#include <math.h>
#include "genlib.h"
#include "simpio.h"

int search(int n);

int main(void)
{
    int number, ri, looptimes;

    looptimes = GetInteger();
    for (ri = 1; ri <= looptimes; ++ri) {
        do {
                number = GetInteger();
        } while (number < 101 || number > 999);
        printf("count=%d\n", search(number));
     }
     return 0;
}

int search(int n) {
    int a, b, c, i, j, limit, count = 0;
    limit = sqrt(n) + 1;
    for (i = 11; i < limit; ++i) {
        j = i * i;
        a = j % 10;
        b = j / 10 % 10;
        c = j / 100;
        if (a == b || b == c || c == a) {
            ++count;
        }
    }
    return count;
}
