#include <stdio.h>
/* try to run,
 gcc demo_def.c and
 gcc -DBINGO demo_def.c
then compare the output to know -D option */

int main()
{
#ifdef BINGO
	printf("12345678, bingo\n");
#else
	printf("87654321, no bingo\n");
#endif
	return (0);
}
