#include <stdio.h>
#include <math.h>

main(argc, argv)
int argc;
char *argv[];
{
	double v, f, f_d;
	double func();
	double func_d();
	scanf("%lf", &v);
	printf("input value:%lf\n", v);

	printf("output function value:%lf\n", f = func(v));
	printf("output derivative value:%lf\n", f_d = func_d(v));
	printf("next value:%lf\n", v - f/f_d);

	return 0;
}


double func(double f)
{
	return (f + 10.0 * exp(f) - 20.0);
}

double func_d(double f)
{
	return (1 + 10.0 * exp(f));
}
