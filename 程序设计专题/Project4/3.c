#include<stdio.h>
int RemoveDuplicates(int * array,int n)
{
	int i,j;
	int temp;
	for(i=0;i < n-1;i++)
	{
		if(array[i] != -1)
			{	
				temp = array[i];
				for(j=i+1;j < n;j++)
				{
					if(array[j] == temp)
						array[j] = 0;
				}
			}
	}
	for(i=0;i<n;i++)
	{
		if(array[i]==0){
			for(j=i;j<n-1;j++)
			array[j]=array[j+1];
			n--;
			i--;
		}
	}
	return n;
}
int main()
{
	int i;
	int a[13] = {65,72,75,79,82,82,84,84,84,86,90,94,95};
	int nScores = 13;
	nScores = RemoveDuplicates(a,nScores);
	for(i=0;i<nScores;i++)
		printf("%3d",a[i]);
}