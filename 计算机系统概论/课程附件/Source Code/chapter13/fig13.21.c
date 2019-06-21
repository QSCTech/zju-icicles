#include <stdio.h>
#define FALSE 0
#define TRUE  1

int main()
{
  int num;
  int divisor;
  int prime;
  
  /* Start at 2 and go until 100  */
  for (num = 2; num <= 100; num++) {
    prime = TRUE;   /* Assume the number is prime */

    /* Test if the candidate number is a prime */
    for (divisor = 2; divisor <= 10; divisor++) 
      if (((num % divisor) == 0) && num != divisor)
        prime = FALSE;

    if (prime)
      printf("The number %d is prime\n", num);
  }
}
