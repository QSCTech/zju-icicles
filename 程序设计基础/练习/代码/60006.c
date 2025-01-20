#include "stdio.h"

int main(void)
{
    int i, j, n, sum;
    int looptimes, ri;
    int a[6][6];

    scanf("%d", &looptimes);
    for(ri = 1; ri <= looptimes; ri++){
        scanf("%d", &n);
		for(i = 0; i < n; ++i) {
			for(j = 0; j < n; ++j) {
                scanf("%d", &a[i][j]);
			}
		}

		--n;
		sum = 0;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				if (i + j != n) {
					sum += a[i][j];
				}
			}
		}

		printf("sum = %d\n", sum);
	}
}