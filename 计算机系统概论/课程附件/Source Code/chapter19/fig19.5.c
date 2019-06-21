#include <stdio.h>

int main() 
{
  int op = 0;  /* Current operation to be perform.        */
  Car carBase; /* carBase an empty head node              */

  carBase.next = NULL;   /* Initialize the list to empty  */

  printf("=========================\n");
  printf("=== Used car database ===\n");
  printf("=========================\n\n");

  while (op != 4) {
    printf("Enter an operation:\n");
    printf("1 - Car aquired. Add a new entry for it.\n");
    printf("2 - Car sold.  Remove its entry.\n");
    printf("3 - Query.  Look up a car's information.\n");
    printf("4 - Quit.\n");
    scanf("%d", &op);

    if (op == 1) 
         AddEntry(&carBase);
    else if (op == 2) 
         DeleteEntry(&carBase);
    else if (op == 3)
         Search(&carBase);
    else if (op == 4)
         printf("Good bye.\n\n");
    else 
         printf("Invalid option.  Try again.\n\n");
  }
}
