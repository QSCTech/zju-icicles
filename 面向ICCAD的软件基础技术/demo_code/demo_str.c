#include <stdio.h>
#include <string.h>

char str[8] = "HELLO";

int main()
{
	char str1[8] = "WORLD!";
	char str2[80] = "HEAVEN?";
	register int i;

	char *str3 = str + 3;
	printf("%s, %d, %d\n", str3, (int)strlen(str), (int)strlen(str3));

	strcat(str, str1);
	for (i=0; i<5; i++) {
		strcat(str1, str);
	}
	printf("\n%s\n", str2);

	strncpy(str2, str3, strlen(str3));
	printf("\n%s\n", str2);

	printf("\n");
}
