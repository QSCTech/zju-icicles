#include <stdio.h>

int main(void)
{
	char c;
	int blank, digit, letter, other;
	int ri, looptimes;

	scanf("%d", &looptimes);
	getchar();
	for(ri = 1; ri<=looptimes; ri++){
		blank = digit = letter = other = 0;
		while ((c = getchar()) != '\n') {
			 if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
				++ letter;
			 } else if (c == ' ') {
				 ++blank;
			 } else if (c >= '0' && c <= '9') {
				 ++digit;
			 } else {
				 ++other;
			 }
		}
		printf("letter = %d, blank = %d, digit = %d, other = %d\n", letter, blank, digit, other);
	}

	return 0;
}
