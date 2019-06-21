#include <stdio.h>

int main()
{
  int dividend;
  int divisor;
  int result;

  printf("Enter the dividend: ");
  scanf("%d", &dividend);

  printf("Enter the divisor: ");
  scanf("%d", &divisor);

  if (divisor != 0) {
    result = dividend / divisor;
    printf("The result of the division is %d\n", result);
  } 
  else 
    printf("A divisor of zero is not allowed\n");
}
