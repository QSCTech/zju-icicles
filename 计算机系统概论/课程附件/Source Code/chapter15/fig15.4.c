#include <stdio.h>

int main()
{
  int year;
  
  printf("Input a year (i.e., 1996): ");
  scanf("%d", &year);
    
  if (year % 4 == 0)
     printf("This year is a leap year"\n);
  else
     printf("This year is not a leap year"\n);
}
