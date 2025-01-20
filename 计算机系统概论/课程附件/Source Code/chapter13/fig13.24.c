#include <stdio.h>

int main()
{
  int operand1, operand2;     /* Input values             */
  int result = 0;             /* Result of the operation  */
  char operation;             /* operation to perform     */
  
  /* Get the input values */
  printf("Enter first operand: ");
  scanf("%d", &operand1);
  printf("Enter operation to perform (+, -, *, /): ");
  scanf("\n%c", &operation);
  printf("Enter second operand: ");
  scanf("%d", &operand2);
  
  /* Perform the calculation */
  switch(operation) {
  case '+':
    result = operand1 + operand2;
    break;
    
  case '-':
    result = operand1 - operand2;
    break;
    
  case '*':
    result = operand1 * operand2;
    break;
    
  case '/':
    if (operand2 != 0)            /* Error-checking code. */
      result = operand1 / operand2;
    else 
      printf("Divide by 0 error!\n");
    break;
    
  default:
    printf("Invalid operation!\n");
    break;
  }

  printf("The answer is %d\n", result);
}
