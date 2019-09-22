#include <stdio.h>

int AllSum(int n);

int main()
{
  int in;                     /* Input value             */
  int sum;                    /* Value of 1+2+3+..+n     */
  
  printf("Input a number: ");
  scanf("%d", &in);
    
  sum = AllSum(in);
  printf("The AllSum of %d is %d\n", in, sum);
}


int AllSum(int n)
{
  int result;                 /* Result to be returned   */
  int i;                      /* Iteration count         */
								    
  for (i = 1; i <= n; i++)    /* This calculates sum     */
    result = result + i;					    
  								    
  return result;              /* Return to caller        */
}
