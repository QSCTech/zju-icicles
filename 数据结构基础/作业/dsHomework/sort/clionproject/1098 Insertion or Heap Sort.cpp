//
// Created by 12638 on 2020/12/15.
//
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn=105;
int heap[maxn];
int heap_size=0;
typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    ElementType  *Elements;
    int Capacity;
    int Size;
};
void swaps(int &a,int &b){
    int tmp;
    tmp=a;
    a=b;
    b=tmp;
}
//  最小值，往下移动， 和左右比较，左右哪个大， 再和父节点比较， 把parent的位置 =child，
//已经把last element叶节点存到【p】了
//调整的过程是不断比较父亲与儿子的值，这里左右儿子都要比较，如果发现父节点小于其中一个子节点，父节点就下去.
/*!
 *
 * @param p begin at p
 * @param H the heap need be processed
 */
void PercolateDown( int p, PriorityQueue H ){
    int tmp = H->Elements[p],child = 2*p;
    while(child <= H->Size  ){    //还没有到底 , we need <= , notice child+1 may into the sorted region , so judge it .
        // swap child and H[p]
        //		printf(" child = %d\n",child);
        if(  tmp < H->Elements[child]){
            if( child+1 <= H->Size && tmp < H->Elements[child+1] ){//child is median
                H->Elements[p] = H->Elements[child+1];
                p = child+1;
                child = 2*p;
            }
            else{       //child is biggest
                H->Elements[p] = H->Elements[child]; // I have a error  , don't change ,I need save tmp instead of H->Elements[p] < H->Elements[child+1]
                p = child;
                child = 2*p;
            }
        }
        else if(child+1 <= H->Size && tmp < H->Elements[child+1]){  //right node bigger than parent
            H->Elements[p] = H->Elements[child+1];
            p = child+1;
            child = 2*p;
        }
        else break;
    }
    H->Elements[p] = tmp;
}
/*
int main()
{
    int n;
    int i;
    int num[maxn],num2[maxn];
    PriorityQueue H = ( PriorityQueue)malloc(sizeof(HeapStruct)); ;  //we  need allocate a room for H
    H->Size = 0;
    scanf("%d",&n);
    for(i = 1;i <= n;i++){  // because we need PercolateDown, child = 2*p;so begin at i =1 not 0
        scanf("%d",&num[i]);
    }
    for(i = 1 ;i <= n;i++){
        scanf("%d",&num2[i]);
    }
    int idx;
    idx = 1;
    for(;idx < n-1 && num2[idx] <= num2[idx+1];idx++);
    int p  = idx + 1;
    for(;p < n && num[p] ==   num2[p];p++);
    if(p == n){  // it is a insertion sort// we conduct a insertion
        sort(num2,num2+idx+2); //sort has first , don't contain second argument
        printf("Insertion Sort\n");
        cout << num2[1];
        for(i = 2;i <= n;i++)
            cout << " "<< num2[i];
    }
    else{
        //heap_pop  swap(0, idx)
        //for(idx = n-1 ;idx > 0  && num2[idx] >= num2[idx-1];idx--); //we cannot find sorted region in this way
        //从n开始往前找，找第一个小于等于b[1]的数字b[p]
        printf("Heap Sort\n");
        for(idx = n-1 ;idx > 0  && num2[idx] >= num2[1];idx--); //idx is in the heap , after idx are sorted
        swaps(num2[1],num2[idx]); //pop max
        idx-- ;
        H->Size = idx;
        H->Elements = num2;
        PercolateDown(1,H);

        // we may need heap
        printf("%d", H->Elements[1]);
        for(int i = 2; i <= n; i++)
            printf(" %d", H->Elements[i]);
        //  heap_down
    }
    return 0;
}
*/
/*
 *   partial accepted  , try the following input
 *
 *   10
3 1 2 8 7 5 9 4 6 0
6 4 5 0 1 2 3 7 8 9
 output 5 4 6 0 1 2 3 7 8 9 error notice child+1 may into the sorted region
 5 4 2 1 0 3 6 7 8 9   2 don't swap with 3 , because..
 */