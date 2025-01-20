#include<stdio.h>

int main(void)
{
	int i, j, m, n, no;
	int num[50];

	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i) {
		num[i] = i;
	}

	no = 0;
	for (i = 1; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			do {
				if (no == n) {
					no = 0;
				}
				++no;
			} while (num[no] == 0);
		}
		num[no] = 0;
		printf("No%d: %d\n", i, no);
	}

	no = 1;
	while(num[no] == 0) {
		++no;
	}
	printf("Last No is: %d\n", no);

	return 0;
}
