#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_comp_asc(const void *str_1, const void *str_2) {
	return strcmp(*(char **)str_1, *(char **)str_2);
}

int main()
{
    int i, j, n = 0;
    char *color[20], str[10], *tmp;

    scanf("%s", str);
    while(str[0] != '#') {
        color[n] = (char *)malloc((strlen(str)+1) * sizeof(char));
        strcpy(color[n], str);
	    ++n;
        scanf("%s", str);
    }

	qsort(color, n, sizeof(char *), str_comp_asc);

	for(i = 0; i < n; i++) {
        printf("%s  ", color[i]);
		free(color[i]);
	}
    printf("\n");

	return 0;
}
