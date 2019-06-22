#include <stdio.h>
#define FALSE 0
#define TRUE  1

int main()
{
  char nextChar;   /* Next character in email address  */
  int gotAt  = FALSE;  /* Indicates if At @ was found  */  
  int gotDot = FALSE;  /* Indicates if Dot . was found */

  printf("Enter your email address: ");

  do {
    scanf("%c", &nextChar);

    if (nextChar == '@')
      gotAt = TRUE;

    if (nextChar == '.' && gotAt == TRUE)
      gotDot = TRUE;
  } 
  while (nextChar != ' ' && nextChar != '\n');
  
  if (gotAt == TRUE && gotDot == TRUE)
    printf("Your email address appears to be valid.\n");
  else
    printf("Your email address is not valid!\n");
}
