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
/* Your function will be put here只是第二个case和第四个case一直通不过，但自己拿来验证的case几乎都是对的，所以琢磨了很久这两个case是什么。刚开始以为最后一个是针对left==right，因为没写这个if的时候这一点是运行超时。后来发现N为奇数的时候，在length=1即两两比较的时候就会出错（sorted里最后一个没有输入），针对这个情况进行修改后，非常意外的，最后一个case通过了，第二个还是错的......所以说，最后一个case是针对奇数情况的。
我测试的例子是N=11
4 5 6 7 8 9 10 11 0 3 1
如果有人这里没通过的话可以试一下是不是这个错......*/
//The function merge_pass performs one pass of the merge sort that merges adjacent pairs of sublists 
//from list into sorted.   let the list into sorted  
  //  N is the number of elements in the list and length is the length of the sublists.
  /* 归并的方法： 将每个元素拆分成大小为1的部分
recursively merge adjacent partitions
  i = 左侧开始项指数 到 右侧最后项指数 的遍历（两端包括）

    如果左侧首值 <= 右侧首值

      拷贝左侧首项的值

    否则： 拷贝右侧部分首值

将元素拷贝进原来的数组中
  */
void merge_pass( ElementType list[], ElementType sorted[], int N, int length ){
    //这个算法和平常的mergesort不同的是，它直接从单个元素的merge开始，一直merge成一个数组，减少了不断递归到单个元素才merge的过程。
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
