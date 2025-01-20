#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main(void)
{
    int reverse(int number);
    
    int m1,m2;
    
    m1 = GetInteger();
    m2 = GetInteger();
    
    printf("%d的逆向是%d\n", m1, reverse(m1));  
    printf("%d的逆向是%d\n", m2, reverse(m2));
    
    return 0;
}

int reverse(int number) {
    int result = 0, negative = 0;
    if (number < 0) {
        number = -number;
        negative = 1;
    }
    while (number > 0) {
        result *= 10;
        result += number % 10;
        number /= 10;
    }
    if (negative) {
        result = -result;
    }
    return result;
}
