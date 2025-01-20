#include <stdio.h>

float matrix(float a[3][3]) {
	int i;
	float sum = 0;
	for (i = 0; i < 3; ++i) {
		sum += a[i][i] + a[i][2 - i];
	}
	sum -= a[1][1];
	return sum;
}

int main()
{
	int i,j;
	float a[3][3];

	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++){
			scanf("%f", &a[i][j]);
		}
	printf("sum=%0.2f \n", matrix(a));

	return 0;
}
