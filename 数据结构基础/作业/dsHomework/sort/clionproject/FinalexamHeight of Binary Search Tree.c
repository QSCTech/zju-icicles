//
// Created by 12638 on 2021/1/26.
//
//#include <stdio.h>
//#include <stdlib.h>
//
//#define MAXN 10
//
//int Height_of_BST( int postorder[], int N );
//
//int main()
//{
//    int postorder[MAXN], N, i;
//
//    scanf("%d", &N);
//    for (i=0; i<N; i++) scanf("%d", &postorder[i]);
//    printf("%d\n", Height_of_BST(postorder, N));
//
//    return 0;
//}
//
///* Your function will be put here */
//int count = 0;
//void printIndent(int n){
//    for (int i = 0; i < n; ++i) {
//        printf("    ");
//    }
//}
//int Height_of_BST( int postorder[], int N ){
//    printIndent(count++);
//    printf("N = %d",N);
//    if (N == 1 || N == 2) {
//        printIndent(--count);
//        printf("return %d\n",N);
//        return  N==1? 1: 2;
//    }
//    int root = postorder[N-1];
//    int i,j;
//    for (i = 0; postorder[i] < root; ++i);// find the pivot, left part smaller than root, right part bigger than root
//    int *a = (int *)malloc(sizeof(int)*i);
//    int *b = (int *)malloc(sizeof(int)*(N-i-1));
//    for (j = 0; j < i; ++j) {
//        a[j] = postorder[j];// copy to a[]
//    }
//    for (int k = 0; k < i; ++k) {
//        printf("a[k] = %d",a[k]);// copy to b[]
//    }
//    int m = 0;
//    for (; j < N-1; ++j) {
//        b[m++] = postorder[j];// copy to b[] ,可能全部倾斜,  b为空或者a为空
//    }
//    for (int k = 0; k < N-i-1; ++k) {
//       printf("b[k] =  %d",b[k]);// copy to b[] b可能为0
//    }
//    printf("\n");
//    int ha,hb;
//    ha = i != 0 ? Height_of_BST(a, i) : 0;
//    hb = i == N - 1 ? 0 : Height_of_BST(b, N - i - 1);
//    printIndent(--count);
//    printf("return ha+1= %d     ",ha+1);
//    printf("     hb+1=  %d\n",hb+1);
//    return hb < ha ? ha + 1 : hb + 1;
//}
