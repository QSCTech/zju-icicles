#include <stdio.h>

int Factorial(int n);           /*! Function Declaration !*/

int main()                      /*  Definition for main   */
{
  int number;                   /*  Number from user      */
  int answer;                   /*  Answer of factorial   */
   							  
  printf("Input a number: ");   /*  Call to printf        */
							  
  scanf("%d", &number);         /*  Call to scanf         */

  answer = Factorial(number);   /*! Call to factorial    !*/

  printf("The factorial of %d is %d\n", number, answer); 
}

int Factorial(int n)            /*! Function Definition  !*/
{				    			  
  int i;                        /*  Iteration count       */
  int result = 1;               /*  Initialized result    */
  				    			  
  for (i = 1; i <= n; i++)      /*  Calculate factorial   */
    result = result * i;	    			  
  							  
  return result;                /*! Return to caller     !*/
}
