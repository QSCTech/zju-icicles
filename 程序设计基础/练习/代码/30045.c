#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    char c;
    int blank, digit, i, letter, other;

    blank = digit = letter = other = 0;
    for (i = 1; i <= 10; ++i) {
        c = getchar();
        if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
            ++letter;
        } else if (c ==  ' ' || c =='\n') {
            ++blank;
        } else if ('0' <= c && c <= '9') {
            ++digit;
        } else {
            ++other;
        }
    }
    printf("letter = %d, blank = %d, digit = %d, other = %d\n", letter, blank, digit, other);
    return 0;
}
