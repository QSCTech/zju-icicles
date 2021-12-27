#include <stdio.h>

int main(argc, argv)
int argc;
char *argv[];
{
	char input_str1[200], input_str2[200];
	printf("ready to get inputs from stdin.\n");
	fscanf(stdin, "%s %s", &input_str1, &input_str2);
	fprintf(stdout, "to stdout %s\n", input_str1);
	fprintf(stderr, "to stderr %s\n", input_str2);
	return 0;
}
