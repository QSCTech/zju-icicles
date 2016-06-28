#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int i, mark;

    for(i = 1; i <= 5; ++i) {
        mark = GetInteger();
        printf(mark < 60 ? "Fail\n" : "Pass\n");
    }
    return 0;
}
