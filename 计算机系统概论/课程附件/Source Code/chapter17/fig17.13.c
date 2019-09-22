#include <stdio.h>

int Fibonacci(int n);

int main()
{
  int in;
  int number;
  
  printf("Which Fibonacci number? ");
  scanf("%d", &in);

  number = Fibonacci(in);
  printf("That Fibonacci number is %d\n", number);
}

int Fibonacci(int n)
{
  int sum;

  if (n == 0 || n == 1)
     return 1;
  else {
     sum = (Fibonacci(n-1) + Fibonacci(n-2));
     return sum;
  }
}
