#include <stdio.h>

/* Function declarations */
double AreaOfCircle(double radius);

int main() 
{
  double outer;                          /* Outer radius */
  double inner;                          /* Inner radius */
  double areaOfRing;                     /* Area of ring */

  printf("Enter outer radius: "); 
  scanf("%lf", &outer);

  printf("Enter inner radius: "); 
  scanf("%lf", &inner);

  areaOfRing = AreaOfCircle(outer) - AreaOfCircle(inner);
  printf("The area of the ring is %f\n", areaOfRing);
}

/* Calculate area of circle given a radius */
double AreaOfCircle(double radius)
{
  double pi = 3.14159265;

  return pi * radius * radius;
}
