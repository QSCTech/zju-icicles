#include <stdio.h>
#include <string.h>

int main(void)
{
	char sx[80], longest[80];
    int i, j, n;
    int looptimes, ri;

    scanf("%d", &looptimes);
    for (ri = 1; ri <= looptimes; ++ri) {
        scanf("%d", &n);
		longest[0] = '\0';
		for (i = 0; i < n; ++i) {
			scanf("%s", sx);
			if (strlen(sx) > strlen(longest)) {
				strcpy(longest, sx);
			}
		}
		printf("The longest is: %s\n", longest);
	}

	return 0;
}
