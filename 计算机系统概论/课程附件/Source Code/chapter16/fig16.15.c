#include <stdio.h>
#define MAX_SIZE 10

int main()
{
  int index;
  int array[MAX_SIZE];
  int limit;

  printf("Enter limit (integer): ");
  scanf("%d", &limit);

  for(index = 0; index < limit; index++) {
    array[index] = 0;
    printf("array[%d] is set to 0\n", index);
  }
}
