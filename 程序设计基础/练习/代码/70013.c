#include<stdio.h>

int main()
{
    char s[80];
    char *p;
    int blank, digit, lower, other, upper;

    gets(s);
    upper = lower = blank = digit = other = 0;
	p = s - 1;
	while (*++p != '\0') {
		if (*p >= 'A' && *p <= 'Z') {
			++upper;
		} else if (*p >= 'a' && *p <= 'z') {
			++lower;
		} else if (*p == ' ') {
			++blank;
		} else if (*p >= '0' && *p <= '9') {
			++digit;
		} else {
			++other;
		}
	}
	printf("upper: %d lower: %d blank: %d digit: %d other: %d\n", upper, lower, blank, digit, other);

	return 0;
}
