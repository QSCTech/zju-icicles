#include <stdio.h>

int globalVar = 2;           /* This variable is global */

int main()
{
  int localVar = 3;   /* This variable is local to main */
  
  printf("Global %d Local %d\n", globalVar, localVar);
  
  {
    int localVar = 4;        /* Local to this sub-block */
    
    printf("Global %d Local %d\n", globalVar, localVar);	
  }
  
  printf("Global %d Local %d\n", globalVar, localVar);
}
