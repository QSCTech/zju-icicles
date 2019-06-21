#include <stdio.h>

int main()
{
   int maxValue;
   int input1;
   int input2;
   
   printf("Input an integer: ");
   scanf("%d", &input1);
   printf("Input another integer: ");
   scanf("%d", &input2);

   maxValue = (input1 > input2) ? input1 : input2;
   printf("The larger number is %d\n", maxValue);
}
