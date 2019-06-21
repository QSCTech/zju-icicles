#include <stdio.h>

int main()
{
  int count;       /* Iteration variable                */
  int numOfTerms;  /* Number of terms to evaluate       */
  double pi = 0;   /* approximation of pi               */
  
  printf("Number of terms (must be 1 or larger) : ");
  scanf("%d", &numOfTerms);

  for (count = 1; count <= numOfTerms; count++) {
    if (count % 2) 
      pi = pi + (4.0 / (2.0 * count - 1)); /* Odd term  */
    else 
      pi = pi - (4.0 / (2.0 * count - 1)); /* Even term */
  }

  printf("The approximate value of pi is %f\n", pi);
}
