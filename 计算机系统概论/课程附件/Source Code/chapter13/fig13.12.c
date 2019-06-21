#include <stdio.h>

int main()
{
  int sum = 0;           /* Initial the result variable */
  int input;             /* Holds user input            */
  int inner;             /* Iteration variables         */
  int outer;  

  /* Get input */
  printf("Input an integer: ");
  scanf("%d", &input);
  
  /* Perform calculation */
  for (outer = 1; outer <= input; outer++)        
    for (inner = 0; inner < outer; inner++) {     
      sum += inner;                  
    }                     
  
  /* Output result */
  printf("The result is %d\n", sum);
}        
