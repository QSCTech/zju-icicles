#include <stdio.h>
#include "genlib.h"

int main(void)
{
    char ch;
    int looptimes, ri;

    /* looptimes = GetInteger(); */
    looptimes = getchar() - '0';
    for (ri = 1; ri <= looptimes; ++ri) {
        ch = getchar();
        switch (ch) {
        case 'A':
            printf("90-100\n");
            break;
        case 'B':
        case 'C':
        case 'D':
            printf("%d-%d\n", 90 - (ch - 'A') * 10, 99 - (ch - 'A') * 10);
            break;
        case 'E':
            printf("0-59\n");
            break;
        default:
            printf("Invalid input\n");
        }
    }
    return 0;
}
