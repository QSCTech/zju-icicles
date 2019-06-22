int RunningSum(int n)
{
  if (n == 1)
     return 1;
  else
     return (n + RunningSum(n-1));
}
