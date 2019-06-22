#include <stdio.h>

int main()
{
  int month;

  printf("Enter the number of the month: ");
  scanf("%d", &month);

  if (month == 4 || month == 6 || month == 9 || month == 11) 
    printf("The month has 30 days\n");
  else if (month == 1 || month == 3 || month == 5  || 
           month == 7 || month == 8 || month == 10 || month == 12)
    printf("The month has 31 days\n");
  else if (month == 2)
    printf("The month has either 28 days or 29 days\n");
  else
    printf("Don't know that month\n");
}
