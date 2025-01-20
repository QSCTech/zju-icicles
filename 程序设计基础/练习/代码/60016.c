#include <stdio.h>
#include <string.h>

/* Chinese character length in GBK */
#define CHAR_LENGTH 2

char str[17];

int main()
{
	void change(char s[4][20]);
	char	s[4][20];
	int i;
	for (i=0; i<4; ++i) {
		scanf("%s",s[i]);
	}
	change(s);
	puts(str);

	return 0;
}

void change(char s[4][20])
{
	int i, pos;
	pos = strlen(s) - CHAR_LENGTH;
	for (i = 0; i < 4; ++i) {
		strcat(str, &s[i][pos]);
	}
}
