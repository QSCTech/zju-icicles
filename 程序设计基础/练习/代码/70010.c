#include<stdio.h>

void main()
{
    char c;
    char str[80];
    int looptimes, ri;
    void delchar(char *str, char c);

    scanf("%d", &looptimes);
    getchar();
    for (ri = 1; ri <= looptimes; ++ri) {
        gets(str);
        scanf("%c", &c);
        getchar();
		
		delchar(str, c);

        printf("result: ");
        puts(str);
    }

	return 0;
}

void delchar(char *str, char c) {
	int i;
	for (i = 0; i < strlen(str); ++i) {
		if (str[i] == c) {
			strcpy(&str[i], &str[i + 1]);
			--i;
		}
	}
}
