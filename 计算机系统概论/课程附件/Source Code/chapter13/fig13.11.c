#include <stdio.h>

int main()
{
  int multiplicand;   /* First operand of each multiply  */
  int multiplier;     /* Second operand of each multiply */

  /* Outer Loop */  
  for (multiplicand = 0; multiplicand < 10; multiplicand++) {
    /* Inner Loop */  
    for (multiplier = 0; multiplier < 10; multiplier++) {
      printf("%d\t", multiplier * multiplicand);
    }
    printf("\n");
  }
}
