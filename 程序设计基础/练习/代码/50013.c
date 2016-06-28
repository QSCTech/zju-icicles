#include <stdio.h>

int main(void)
{
    int count, in;
    int looptimes, ri;

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%d", &in);
        count = 1;
        while ((in /= 10) != 0) {
            ++ count;
        }
        printf("count = %d\n", count);
    }

    return 0;
}
