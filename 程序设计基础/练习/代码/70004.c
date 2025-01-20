#include "stdio.h"
#include "string.h"

#define MAXLEN 80

int main(void)
{
    char ch;
    char str[MAXLEN];
    int i;
    int looptimes, ri;

    scanf("%d", &looptimes);
    getchar();
    for (ri = 1; ri <= looptimes; ++ri) {
        i = 0;
        while((ch = getchar()) != '\n'){
			if (ch >= 'A' && ch <= 'Z') {
				ch =  'A' + 'Z' - ch;
			}
            str[i++] = ch;
		}
        str[i] = 0;

      	printf("After replaced: ");
		for (i = 0; str[i] != 0; ++i) {
            putchar(str[i]);
		}
		putchar('\n');
	}

	return 0;
}
