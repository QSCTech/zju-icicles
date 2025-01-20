#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}
void  merge_sort( ElementType list[],  int N ){
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 
int main(){
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}
/* Your function will be put hereֻ�ǵڶ���case�͵��ĸ�caseһֱͨ���������Լ�������֤��case�������ǶԵģ�������ĥ�˺ܾ�������case��ʲô���տ�ʼ��Ϊ���һ�������left==right����Ϊûд���if��ʱ����һ�������г�ʱ����������NΪ������ʱ����length=1�������Ƚϵ�ʱ��ͻ����sorted�����һ��û�����룩����������������޸ĺ󣬷ǳ�����ģ����һ��caseͨ���ˣ��ڶ������Ǵ��......����˵�����һ��case�������������ġ�
�Ҳ��Ե�������N=11
4 5 6 7 8 9 10 11 0 3 1
�����������ûͨ���Ļ�������һ���ǲ��������......*/
//The function merge_pass performs one pass of the merge sort that merges adjacent pairs of sublists 
//from list into sorted.   let the list into sorted  
  //  N is the number of elements in the list and length is the length of the sublists.
  /* �鲢�ķ����� ��ÿ��Ԫ�ز�ֳɴ�СΪ1�Ĳ���
recursively merge adjacent partitions
  i = ��࿪ʼ��ָ�� �� �Ҳ������ָ�� �ı��������˰�����

    ��������ֵ <= �Ҳ���ֵ

      ������������ֵ

    ���� �����Ҳಿ����ֵ

��Ԫ�ؿ�����ԭ����������
  */
void merge_pass( ElementType list[], ElementType sorted[], int N, int length ){
    //����㷨��ƽ����mergesort��ͬ���ǣ���ֱ�Ӵӵ���Ԫ�ص�merge��ʼ��һֱmerge��һ�����飬�����˲��ϵݹ鵽����Ԫ�ز�merge�Ĺ��̡�
    // at first , length =1 ; 
    //  we pass the list[]  into sorted[] . length . 
	int i ;
	ElementType tmp;
	int p1 ,p2; 
	// 
	for(i = 0 ; i < N ;i = i + 2*length ){
		p1 = i; 
		p2 = i + length;
		while( p2 < i+ 2*length && p1 < i+length ){
			if(list[p1] < list[p2])
     		sorted[pb++] = list[p1++];
     		else
     		sorted[pb++] = list[p2++];
		}
		// move the rest of array
	  	while(p1 < i+length ){
	    	sorted[pb++] = list[p1++];
		}
		while(p2 < i+ 2*length){
	    	sorted[pb++] = list[p1++];
		}
  	}
   
}
