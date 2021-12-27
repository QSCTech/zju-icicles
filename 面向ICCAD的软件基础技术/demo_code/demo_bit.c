#include <stdio.h>
#include <stdlib.h>

extern int bit_count();

int main(int argc, char **argv)
{
	unsigned long int n;
	int c;
	if(argc<2) {
		fprintf(stderr, "at least one number needed\n");
		return(1);
	}
	n = atol(argv[1]);
	printf("input number in hexadecimal: %lx \n", n);
	c = bit_count(n);
	printf("totally %d bit(s) in one\n", c);
	return(0);
}

