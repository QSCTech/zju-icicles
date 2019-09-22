/* Include the standard I/O header file */
#include <stdio.h>

int inGlobal;    /* inGlobal is a global variable because */
                 /* it is declared outside of all blocks  */
		 
int main()	 
{		 
  int inLocal;   /* inLocal, outLocalA, outLocalB are all */
  int outLocalA; /* local to main                         */
  int outLocalB;
  
  /* Initialize */
  inLocal  = 5;
  inGlobal = 3;
  
  /* Perform calculations */
  outLocalA = inLocal & ~inGlobal;
  outLocalB = (inLocal + inGlobal) - (inLocal - inGlobal);  
  
  /* Print out results */
  printf("outLocalA = %d, outLocalB = %d\n", outLocalA, outLocalB);
}
