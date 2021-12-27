#include <stdio.h>
#include <math.h>
int main()
{
#define PI 3.14159
	float angle = PI; float value;
	auto float a, b, c;
	float q_angle = angle / 4.0; 
	value = sin(q_angle);
	printf("sine 45 = %g\n",value);
}
