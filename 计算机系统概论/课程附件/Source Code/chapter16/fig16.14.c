#include <stdio.h>
#define MAX_NUMS 10

void InsertionSort(int list[]);

int main()
{
  int index;              /* iteration variable          */
  int numbers[MAX_NUMS];  /* list of number to be sorted */

  /* Get input */
  printf("Enter %d numbers.\n", MAX_NUMS);
  for (index = 0; index < MAX_NUMS; index++) {
    printf("Input number %d : ", index);
    scanf("%d", &numbers[index]);
  }

  InsertionSort(numbers);  /* Call sorting routine       */

  /* Print sorted list */
  printf("\nThe input set, in ascending order:\n");
  for (index = 0; index < MAX_NUMS; index++) 
    printf("%d\n", numbers[index]);
}

void InsertionSort(int list[])
{
  int unsorted;         /* index for unsorted list items */
  int sorted;           /* index for sorted items        */
  int unsortedItem;     /* Current item to be sorted     */

  /* This loop iterates from 1 thru MAX_NUMS  */
  for (unsorted = 1; unsorted < MAX_NUMS; unsorted++) {  
    unsortedItem = list[unsorted];

    /* This loop iterates from unsorted thru 0, unless 
       we hit an element smaller than current item */
    for (sorted = unsorted - 1; 
         (sorted >= 0) && (list[sorted] > unsortedItem); 
         sorted--) 
      list[sorted + 1] = list[sorted];
        
    list[sorted + 1] = unsortedItem; /* Insert item      */
  }
}
