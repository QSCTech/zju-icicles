#include <stdio.h>

void Swap(int firstVal, int secondVal);

int main()
{
  int valueA = 3;
  int valueB = 4;
  
  printf("Before Swap ");
  printf("valueA = %d and valueB = %d\n", valueA, valueB);

  Swap(valueA, valueB);

  printf("After  Swap ");
  printf("valueA = %d and valueB = %d\n", valueA, valueB);
}

void Swap(int firstVal, int secondVal)
{
  int tempVal;          /* Holds firstVal when swapping */
  
  tempVal = firstVal;
  firstVal = secondVal;
  secondVal = tempVal;
}
