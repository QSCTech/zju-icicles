#include <stdio.h>

int main(void)
{
    int i, n, temp;
    int looptimes, ri;
    int a[10];

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%d", &n);
		for (i = n - 1; i >= 0; --i) {
            scanf("%d", &a[i]);
		}
        for(i = 0; i < n; ++i)
            printf("%d ", a[i]);
        printf("\n");
    }

}
