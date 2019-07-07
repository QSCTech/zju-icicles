#include<stdio.h>
void SortIntegerArray(int * a)
{
	int i = 0;  
    int j = 0;  
    int tmp = 0;  
    for(i = 1;i<8;i++)  
    {  
      tmp = a[i];   
      j = i-1; 
      while(j>=0 && tmp<a[j])  
      {  
        a[j+1] = a[j];
        j--;   
      }  
      a[j+1] = tmp;
    }  
  }  
int main()
{
	int i;
	int a[8]={31,41,59,26,53,58,97,93};
	SortIntegerArray(a);
	for(i=0;i<8;i++)
	printf("%3d\n", a[i]);
}