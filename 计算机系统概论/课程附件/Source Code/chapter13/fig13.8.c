#include <stdio.h>

int main()
{
  char echo = 'A';   /* Initialize char variable echo */
  
  while (echo != '\n') {
    scanf("%c", &echo);
    printf("%c", echo);
  }
}
