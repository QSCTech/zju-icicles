#include "stdio.h"

int main(void)
{
	int flag, i, j, k, row, col, n;
	int a[6][6];
	int looptimes, ri;

	scanf("%d", &looptimes);
	for (ri = 1; ri <= looptimes; ++ri) {
		scanf("%d", &n);
		for (i = 0; i < n; ++i) {
			for(j = 0; j < n; ++j) {
				scanf("%d", &a[i][j]);
			}
		}

		flag = 0;
		for (row = 0; row < n; ++row) {
			col = 0;
			for (j = 0; j < n; ++j) {
				if (a[row][j] > a[row][col]) {
					col = j;
				}
			}
			for (i = 0; i < n; ++i) {
				if (a[i][col] < a[row][col]) {
					flag = 2;
					break;
				}
			}
			if (flag == 2) {
				flag = 0;
			} else {
				flag = 1;
				break;
			}
		}

		if(flag != 0) {
			printf("a[%d][%d] = %d\n", row, col,a[row][col]);
		} else {
			printf("NO\n");
		}
	}

	return 0;
}
