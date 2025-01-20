#include <stdio.h>

int main()
{
    char s[80];
    int looptimes, ri;
    int mirror(char *p);

    scanf("%d", &looptimes);
    getchar();
    for (ri = 1; ri <= looptimes; ++ri) {
        gets(s);
        if(mirror(s) != 0)
      	    printf("YES\n");
        else
            printf("NO\n");
    }

	return 0;
}

int mirror(char *p) {
	int i, length, half;
	length = strlen(p);
	half = length / 2;
	for (i = 0; i < half; ++i) {
		if (p[i] != p[length - 1 - i]) {
			return 0;
		}
	}
	return 1;
}
