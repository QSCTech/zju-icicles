#include <stdio.h>
#include <unistd.h>

int main()
{
	int pid;

	printf("two eyes cannot be shown together if in one process.\n");

	if ((pid = fork()) == 0) {
		printf("in child\n");
		system("xeyes -fg red +shape");
	} else if (pid){
		printf("in parent\n");
		system("xeyes -fg green +shape");
	} else {
		fprintf(stderr, "error\n");
	}
}
