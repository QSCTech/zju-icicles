#include "stdio.h"
#include "math.h"

int main(void)
{
    int flag, i, j, n;
    int a[6][6];
    int looptimes, ri;

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%d", &n);
		flag = 1;
		for (i = 0; i < n; ++i) {
			for(j = 0; j < n; ++j) {
                scanf("%d", &a[i][j]);
				if (i > j && a[i][j] != 0) {
					flag = 0;
				}
			}
		}

		if (flag != 0) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}

	return 0;
}
