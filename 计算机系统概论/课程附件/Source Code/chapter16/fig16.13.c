#include <stdio.h>
#define MAX_STRING 20

int StringLength(char string[]);
void CharSwap(char *firstVal, char *secondVal);
void Reverse(char string[]);

int main()
{
  char input[MAX_STRING];            /* Input string */
  
  printf("Input a word (less than 20 characters): ");
  scanf("%s", input);

  Reverse(input);
  printf("The word reversed is %s.\n", input);
}

int StringLength(char string[])
{
  int index = 0;

  while (string[index] != '\0') 
    index = index + 1;

  return index;
}

void CharSwap(char *firstVal, char *secondVal)
{
  char tempVal;   /* Temporary location for swapping */
  
  tempVal = *firstVal;
  *firstVal = *secondVal;
  *secondVal = tempVal;
}

void Reverse(char string[])
{
  int index;
  int length;

  length = StringLength(string);
  
  for (index = 0; index < (length / 2); index++) 
    CharSwap(&string[index], &string[length - (index + 1)]);
}
