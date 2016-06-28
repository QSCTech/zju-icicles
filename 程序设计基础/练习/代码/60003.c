#include <stdio.h>

int main(void)
{
	int i, smallest, greatest, n, t;
	int looptimes, ri;
	int a[10];

	scanf("%d", &looptimes);
	for(ri = 1; ri <= looptimes; ++ri) {
		scanf("%d", &n);
		smallest = greatest = 0;
		for (i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			if (a[i] < a[smallest]) {
				smallest = i;
			} else if (a[i] > a[greatest]) {
				greatest = i;
			}
		}
		if (smallest != 0) {
			t = a[0];
			a[0] = a[smallest];
			a[smallest] = t;
			if (greatest == 0) {
				greatest = smallest;
			} else if (greatest == smallest) {
				greatest = 0;
			}
		}
		if (greatest != n - 1) {
			t = a[n - 1];
			a[n - 1] = a[greatest];
			a[greatest] = t;
		}
		printf("After swap: ");
		for (i = 0; i < n; ++i) {
			printf("%d ", a[i]);
		}
		printf("\n");
	}
	return 0;
}
