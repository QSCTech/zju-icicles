#include <stdio.h>

int main(void)
{
    int i, index, n;
    int ri, looptimes;
    int a[10];

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%d", &n);
		index = 0;
		for (i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
			if (a[i] > a [index]) {
				index = i;
			}
		}
		printf("max = %d, index = %d\n", a[index], index);
	}

	return 0;
}
