#include <stdio.h>
#include <string.h>

int main()
{
	int n, cur, max = 0;
	char s[80];

	scanf("%d",&n);
	while (n--) {
		gets(s);
		if ((cur = strlen(s)) > max) {
			max = cur;
		}
	}

	printf("length=%d\n", max);

	return 0;
}
