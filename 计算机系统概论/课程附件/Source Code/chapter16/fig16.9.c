#include <stdio.h>
#define MAX_NUMS 10

int main()
{
  int index;              /* Loop iteration variable     */
  int repIndex;           /* Loop variable for rep loop  */
  int numbers[MAX_NUMS];  /* Original input numbers      */
  int repeats[MAX_NUMS];  /* Number of repeats           */

  /* Get input */
  printf("Enter %d numbers.\n", MAX_NUMS);
  for (index = 0; index < MAX_NUMS; index++) {
    printf("Input number %d : ", index);
    scanf("%d", &numbers[index]);
  }

  /* Scan through entire array, counting number of       */
  /* repeats per element within the original array       */
  for (index = 0; index < MAX_NUMS; index++) {
    repeats[index] = 0;
    for (repIndex = 0; repIndex < MAX_NUMS; repIndex++) {
      if (numbers[repIndex] == numbers[index])
        repeats[index]++;
    }
  }
  
  /* Print the results */
  for (index = 0; index < MAX_NUMS; index++) 
    printf("Original number %d.  Number of repeats %d\n", 
           numbers[index], repeats[index]);  
}
