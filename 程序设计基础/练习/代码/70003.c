#include "stdio.h"

#define MAXLEN 80

int main(void)
{
    char ch;
    char str[MAXLEN];
    int count, i;
    int looptimes, ri;

    scanf("%d", &looptimes);
    getchar();
    for (ri = 1; ri <= looptimes; ++ri) {
        i = 0;
        while ((ch = getchar()) != '\n') {
            str[i++]=ch;
        }
        str[i] = 0;

		count = 0;
		for (--i; i >=0; --i) {
			if (str[i] > 'A' && str[i] <= 'Z' \
				&& str[i] != 'E' \
				&& str[i] != 'I' \
				&& str[i] != 'O' \
				&& str[i] != 'U') {
					++count;
			}
		}

		printf("count = %d\n", count);
	}

	return 0;
}
