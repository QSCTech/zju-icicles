#include <stdio.h>

void IntToAscii(int i);

int main()
{
  int in;
  
  printf("Input number: ");
  scanf("%d", &in);

  IntToAscii(in);
  printf("\n");
}

void IntToAscii(int num)
{
  int prefix;
  int currDigit;  

  if (num < 10)               /* The terminal case     */
    printf("%c", num + '0');
  else {                                                    
    prefix = num / 10;        /* Convert the number    */
    IntToAscii(prefix);       /* without last digit    */

    currDigit = num % 10;     /* Then print last digit */
    printf("%c", currDigit + '0');
  }
}
