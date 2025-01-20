#include <stdio.h>

int main(void)
{
    int count, in, sum;
    int looptimes, ri;

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%d", &in);
        if (in < 0) {
            in = -in;
        }
        count = 0;
        sum = 0;
        do {
            ++count;
            sum += in % 10;
            in /= 10;
        } while (in != 0);
        printf("count = %d, sum = %d\n", count, sum);
    }

   	return 0;
}
