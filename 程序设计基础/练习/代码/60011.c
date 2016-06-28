#include <stdio.h>

int main()
{
	int i, index, n, temp;
	int looptimes, ri;
	int a[10];

	scanf("%d", &looptimes);
	for (ri = 1; ri <= looptimes; ++ri) {
		scanf("%d", &n);
		index = 0;
		for (i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			/* Using > or >= is not specified in the problem... */
			if (a[i] >= a[index]) {
				index = i;
			}
		}
		printf("max = %d, index = %d\n", a[index], index);
		if (index != n - 1) {
			temp = a[n - 1];
			a[n - 1] = a[index];
			a[index] = temp;
		}
		for (i = 0; i < n; ++i) {
			printf("%d ", a[i]);
		}
		printf("\n");
	}

	return 0;
}
