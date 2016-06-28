#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[80] = {0}, max[] = {0};
    int i;

	for (i = 0; i < 5; ++i) {
		scanf("%s", str);
		if (strcmp(str, max) > 0) {
			strcpy(max, str);
		}
	}

    printf("Max is: %s\n", max);

	return 0;
}
