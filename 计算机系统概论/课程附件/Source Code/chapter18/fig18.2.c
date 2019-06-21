#include <stdio.h>
#include <unistd.h>

int main()
{
  putchar('a');

  sleep(5);
    
  putchar('b');
  putchar('\n');
}
