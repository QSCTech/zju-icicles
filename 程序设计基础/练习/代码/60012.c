#include <stdio.h>

void mov(int *x, int n, int m);

int main(void)
{
	int i, m, n;
	int a[80];

	scanf("%d%d", &n, &m);
	for (i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}

	mov(a, n, m);

	printf("After move: ");
	printf("%d", a[0]);
	for (i = 1; i < n; ++i) {
		 printf(" %d", a[i]);
	}
	printf("\n");

	return 0;
}

void mov(int *x, int n, int m) {
	int i, t;
	int y[80];
	t = n - m;
	for (i = 0; i < t; ++i) {
		y[i + m] = x[i];
	}
	for (i = n - m; i < n; ++i) {
		y[i + m - n] = x[i];
	}
	for (i = 0; i < n; ++i) {
		x[i] = y[i];
	}
}
