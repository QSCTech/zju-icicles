#include <stdio.h>
#include <math.h>

main(argc, argv)
int argc;
char *argv[];
{
	double x, y, f1, f2, f1_x, f1_y, f2_x, f2_y;
	double func1(), func2();
	double func1_dx(), func1_dy(), func2_dx(), func2_dy();
	scanf("%lf, %lf", &x, &y);
	printf("input value:%lf, %lf\n", x, y);

	printf("output function values:%lf, %lf\n",f1=func1(x,y),f2=func2(x,y));

	printf("output derivative values:%lf,%lf\n", f1_x=func1_dx(x,y), f1_y=func1_dy(x,y));
	printf("output derivative values:%lf,%lf\n", f2_x=func2_dx(x,y), f2_y=func2_dy(x,y));
/*
	f1_x f1_y   deltax    f1
	f2_x f2_y * deltay =- f2
*/
	double deltax, deltay;
	deltax = - (f1*f2_y-f2*f1_y)/(f1_x*f2_y-f2_x*f1_y);
	deltay = - (f1_x*f2-f2_x*f1)/(f1_x*f2_y-f2_x*f1_y);

	printf("output delta values:%lf,%lf\n", deltax, deltay);
	printf("output iterative values:%lf,%lf\n", x+deltax, y+deltay);
	return 0;
}


double func1(double x, double y)
{
	return(x*x-2.0*x*y+y*y-y*y*y); 
}

double func2(double x, double y)
{
	return(y*y*y+x-3.0); 
}

double func1_dx(double x, double y)
{
	return(2.0*x-2.0*y);
}

double func1_dy(double x, double y)
{
	return(-2.0*x+2.0*y-3.0*y*y);
}

double func2_dx(double x, double y)
{
	return(1.0);
}

double func2_dy(double x, double y)
{
	return(3.0*y*y);
}

