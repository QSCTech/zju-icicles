#include<stdio.h>
#include<string.h>

int main()
{
    char s[80];
    int m;
    int looptimes, ri;

    scanf("%d", &looptimes);
    getchar();
    for (ri = 1; ri <= looptimes; ++ri) {
        gets(s);
        scanf("%d", &m);
        getchar();
		if (strlen(s) < m) {
            printf("error input");
		} else{
            puts(&s[m - 1]);
        }
	}

	return 0;
}
