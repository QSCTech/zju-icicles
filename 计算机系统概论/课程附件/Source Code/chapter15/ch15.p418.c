int Factorial(int n)
{
  int i;                /* Iteration count           */
  int result = 1;       /* Initialized result        */
								    
  /* Check for legal parameter values */  			    
  if (n < 1 || n > 31) {					    
    printf("Bad input. Input must be >= 1 and <= 31.\n");	    
    return -1;							    
  }								    
								    
  for (i = 1; i <= n; i++)  /* Calculates factorial  */
    result = result * i;					    
  								    
  return result;            /* Return to caller      */
}
