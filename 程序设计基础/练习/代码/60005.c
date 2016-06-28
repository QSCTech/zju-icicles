#include <stdio.h>

int main(void)
{
    int i, j, m, n, sum;
    int a[6][6];

    scanf("%d%d",&m,&n);
	for (i = 0; i < m; ++i) {
		sum = 0;
		for (j = 0; j < n; ++j) {
            scanf("%d", &a[i][j]);
			sum += a[i][j];
		}
		printf("sum of row %d is %d\n", i, sum);
	}

	return 0;
}
