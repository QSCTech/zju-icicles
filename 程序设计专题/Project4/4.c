#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void RanArray(int * array)
{
	int temp = array[0];
	int tempi;
	int tempj;
	int j = 0 ;
	int i;
	int count;
	for(i=0;i<52;i++)
	{
		for(j=0;j<52;j++)
		{
			if(array[j] <= temp)
			{
				tempi = j;
				temp = array[j];
			}
		}
		srand((unsigned int)time(NULL)+(unsigned int)(tempj*tempj+7*temp+5*temp));
		for(count=0;count<10000000;count++); 
		tempj = rand()%52;
		temp = array[tempi];
		array[tempi] = array[tempj];
		array[tempj] =  temp;
	}
}
int main()
{
	int a[52];
	int i;
	for(i=0;i<52;i++)
		a[i]=i+1;
	RanArray(a);
	for(i=0;i<52;i++)
		printf("%3d\n",a[i]);
	
}