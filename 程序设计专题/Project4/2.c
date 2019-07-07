#include<stdio.h>
int RemoveZeroElement(int * a,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		if(a[i]==0){
			for(j=i;j<n-1;j++)
			a[j]=a[j+1];
			n--;
			i--;
		}
	}
	return n;
}
int main()
{
	int i,j;
	int a[10]={0,1,0,3,4,5,6,7,8,0};
	i=RemoveZeroElement(a,10);
	for(j=0;j<i;j++)
	printf("%2d",a[j]);
}