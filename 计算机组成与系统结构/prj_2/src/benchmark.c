#include "util.h"

#define MUL_DATA_SIZE 5
#define DIV_DATA_SIZE 5
#define REM_DATA_SIZE 5
// 5 use for mul, 5 use for div and 5 use for rem
#define DATA_SIZE 15

int input_data1[DATA_SIZE] = 
{
   41,   454, 833,  -335, -100,
   110, 2500, 989,  -749, -10365, 
   50,    13, -43, -9021, -2819
};

int input_data2[DATA_SIZE] = 
{
  195,  543,  -960, -649,  566, 
   53, -403,   788,  346, -531, 
   23,   -7,   -32,   97,  101
};

int verify_data[DATA_SIZE] = 
{
  7995, 246522, -799680, 217415, -56600, 
     2,     -6,       1,     -2,     19,
     4,      6,     -11,      0,    -92
};

int mul(int a,int b)
{
  return a * b;
}

int div(int a,int b)
{
  return a / b;
}

int rem(int a,int b){
  return a % b;
}

int main( int argc, char* argv[] )
{
  int i;
  int results_data[DATA_SIZE];

#if PREALLOCATE
  for (i = 0; i < MUL_DATA_SIZE; i++)
  {
    results_data[i] = mul(input_data1[i], input_data2[i]);
  }
  for (i = MUL_DATA_SIZE; i < MUL_DATA_SIZE + DIV_DATA_SIZE; i++)
  {
    results_data[i] = div(input_data1[i], input_data2[i]);
  } 
  for(i = MUL_DATA_SIZE + DIV_DATA_SIZE;i < DATA_SIZE;i++)
  {
    results_data[i] = rem(input_data1[i],input_data2[i]);
  }
#endif

  setStats(1);
  for (i = 0; i < MUL_DATA_SIZE; i++)
  {
    results_data[i] = mul(input_data1[i], input_data2[i]);
  }
  for (i = MUL_DATA_SIZE; i < MUL_DATA_SIZE + DIV_DATA_SIZE; i++)
  {
    results_data[i] = div(input_data1[i], input_data2[i]);
  } 
  for(i = MUL_DATA_SIZE + DIV_DATA_SIZE;i < DATA_SIZE;i++)
  {
    results_data[i] = rem(input_data1[i],input_data2[i]);
  }
  setStats(0);

  // Check the results
  return verify( DATA_SIZE, results_data, verify_data );
}
