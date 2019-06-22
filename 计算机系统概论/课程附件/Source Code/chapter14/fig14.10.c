#include <stdio.h>

/* Function declaration */
char ToUpper(char inchar);
 
/* Function main:                                        */
/* Prompt for a line of text, Read one character,        */
/* convert to uppercase, print it out, then get another  */
int main()
{
  char echo = 'A';         /* Initialize input character */
  char upcase;                 /* Converted character    */
  
  while (echo != '\n') {
    scanf("%c", &echo);
    upcase = ToUpper(echo);
    printf("%c", upcase);
  }
}

/* Function ToUpper:                                     */
/* If the parameter is lower case return                 */
/* its uppercase ASCII value                             */
char ToUpper(char inchar)
{
  char outchar;

  if ('a' <= inchar && inchar <= 'z')
    outchar = inchar - ('a' - 'A');
  else
    outchar = inchar;

  return outchar;
}
