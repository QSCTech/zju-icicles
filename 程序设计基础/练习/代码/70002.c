#include "stdio.h"

#define MAXLEN 80

int main(void)
{
    char cc, ch;
    char str[MAXLEN];
    int count, flag, i, index;
    int looptimes, ri;

    scanf("%d", &looptimes);
    getchar();
    for (ri = 1; ri <= looptimes; ++ri) {
        cc = getchar();
        getchar();

        i = 0;
        while ((ch = getchar()) != '\n'){
            str[i++] = ch;
        }
        str[i] = 0;

		flag = 0;
		for (--i; i >= 0; --i) {
			if (str[i] == cc) {
				index = i;
				flag = 1;
				break;
			}
		}
		if (flag != 0) {
            printf("index = %d\n", index);
		} else {
			printf("Not Found\n");
		}
	}

	return 0;
}
