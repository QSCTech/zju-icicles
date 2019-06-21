#include <stdio.h>

#define RADIUS  15.0     /* This value is in centimeters */

int main()
{
  const double pi = 3.14159;     
  double area;
  double circumference;
  
  /* Calculations */  
  area = pi * RADIUS * RADIUS;          /* area = pi*r^2 */
  
  circumference = 2 * pi * RADIUS;    /* circumference = */
                                      /*          2*pi*r */
  
  printf("Area of a circle with radius %f cm is %f cm^2\n", 
         RADIUS, area);
  
  printf("Circumference of the circle is %f cm\n", 
        circumference);         
}
