#include <stdio.h>

int Squared(int x);

int main() 
{
  int sideA;
  int sideB;
  int sideC;
  int maxC;

  printf("Enter the maximum length of hypotenuse: ");
  scanf("%d", &maxC);

  for (sideC = 1; sideC <= maxC; sideC++) {
    for (sideB = 1; sideB <= maxC; sideB++) {
      for (sideA = 1; sideA <= maxC; sideA++) {        
        if (Squared(sideC) == Squared(sideA) + Squared(sideB))
          printf("%d %d %d\n", sideA, sideB, sideC);
      }
    }
  }
}

/* Calculate the square of a number */
int Squared(int x)
{
  return x * x;
}
