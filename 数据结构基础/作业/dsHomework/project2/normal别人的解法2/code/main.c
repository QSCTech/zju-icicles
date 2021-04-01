#include <stdio.h>
#include <stdlib.h>
#include "person.h"

person People;
#define PERSON(x) (People+(x))//handy for fetch person whose index is x

#define AGEMAX 200
int ageCnt[AGEMAX+1];//[0,AGEMAX],0 unused
int * ageBucket[AGEMAX+1];//[0,AGEMAX],0 unused, Bucket Table

void Sort(int age);//Bucket Table Sort
void printQuery(int m,int Amin,int Amax);//each Query, call this function

int main()
{
    int n,k,m,i,age,Amin,Amax,Atmp;
    fscanf(stdin,"%d %d",&n,&k);
    People = (person)malloc(n*sizeof(_person));//dynamic malloc memory for saving space when unnecessary
    person ptr;
    for(ptr=People,i=0;i<n;i++,ptr++)
    {
        fscanf(stdin,"%s %d %d",ptr->name,&(ptr->age),&(ptr->worth));
        ageCnt[ptr->age]++;//prepare for the following malloc size, how many index space should be malloc
    }

    /*Bucket Table Sort*/
    for(age=1;age<=AGEMAX;age++)//create Bucket Table
    {
        ageBucket[age] = (int*)malloc((ageCnt[age]+1)*sizeof(int));
        //ageBucket[i] = age==i, sorted Table of worth, that is
        //ageBucket[i][j] is the index of sorted array in age==i, that is
        //People[ageBucket[i][j]] is the j-th richest in people aged i
        ageBucket[age][ageCnt[age]] = -1;
        //-1 , who acts like '\0' in the char array(string),
        //is a boundary telling that it's the end.
        //In other words, the people aged i are all visited when -1 appears.
        
        ageCnt[age] = 0;
        //prepare for the next for-loop 's index
        //reuse this array for saving the space of sizeof(int)*(AGEMAX+1)
    }
    for(ptr=People,i=0;i<n;i++,ptr++)//divide into Buckets
    {
        ageBucket[ptr->age][ageCnt[ptr->age]++] = i;
        //ageCnt[ptr->age]++ means the putting procedure is in such a order : 0,1,...,cnt-1
    }
    for(age=1;age<=AGEMAX;age++)//Sort in each Bucket
    {
        Sort(age);
    }
    /*Bucket Table Sort*/
    
    for(i=0;i<k;i++)//Query
    {
        scanf("%d %d %d",&m,&Amin,&Amax);
        if(Amin>Amax)//ensure Amin<=Amax
        {
            Atmp = Amin;
            Amin = Amax;
            Amax = Atmp;
        }
        printf("Case #%d:\n",i+1);
        printQuery(m,Amin,Amax);
    }
}

/*Bucket Table Sort Implement*/
#define INDEXb(x) (ageBucket[age][(x)])//Handy for acquire index of People by index of Bucket Table
#define COMPARE_BUCKET(i,j) comparePerson(PERSON(INDEXb(i)),PERSON(INDEXb(j)))//return Order(i)>Order(j)
void quickSort(int age,int l,int r)//to-do 3-median, max->min
{
    int i,j,tmp,len = r-l;
    if(len<=20)//small len => Insertion Sort, which would be quicker
    {
        for(i=l;i<r;i++)
        {
            for(j=i+1;j>l&&COMPARE_BUCKET(j,j-1);j--)
            {
                tmp = INDEXb(j);
                INDEXb(j) = INDEXb(j-1);
                INDEXb(j-1) = tmp;
            }
        }
    }
    else//Quick Sort 3-median version
    {
        int m = (l+r)/2;//median
        int pivot;
        
        //make Order(l)>Order(r)
        if(COMPARE_BUCKET(r, l))//if Order(l)<Order(r), exchange l&r
        {
            tmp = INDEXb(l);
            INDEXb(l) = INDEXb(r);
            INDEXb(r) = tmp;
        }
        
        if(COMPARE_BUCKET(m, l))//Order(m)>Order(l)>Order(r)
        {
            pivot = INDEXb(l);//make median as pivot
            INDEXb(l) = INDEXb(m);//put biggest to the left
            INDEXb(m) = INDEXb(l+1);//let i = l+1 become a hole
        }
        
        else if(COMPARE_BUCKET(r, m))//Order(l)>Order(r)>Order(m)
        {
            pivot = INDEXb(r);//make median as pivot
            INDEXb(r) = INDEXb(m);//put smallest to the right
            INDEXb(m) = INDEXb(l+1);//let i = l+1 become a hole
        }
        else//Order(l)>Order(m)>Order(r)
        {
            pivot = INDEXb(m);//make median as pivot
            INDEXb(m)=INDEXb(l+1);//let i = l+1 become a hole
        }
        //Notice : i=l+1 is the first index(of Table),
        //to be filled by first Order(j) < Order(pivot), j from r-1 to i
        //So call a HOLE
        
        for(i=l+1,j=r-1;i<j;)
        {
            while(i<j&&comparePerson(PERSON(pivot),PERSON(INDEXb(j)))){j--;}//get j : Order(j) < Order(pivot)
            INDEXb(i)=INDEXb(j);// put such j into the hole i, the left part of pivot, creating new hole j
            while(i<j&&comparePerson(PERSON(INDEXb(i)),PERSON(pivot))){i++;}//get i : Order(i) > Order(pivot)
            INDEXb(j)=INDEXb(i);// put such i into the hole j, the right part of pivot, creating new hole i
        }
        INDEXb(i)=pivot;//i=j, the final hole for the pivot
        
        quickSort(age,l,i-1);//division for left part
        quickSort(age,j+1,r);//division for left part
    }
}
void Sort(int age)//auto function for calling quickSort
{
    quickSort(age,0,ageCnt[age]-1);
}
/*Bucket Table Sort Implement*/

typedef int * heapNode;
typedef struct{
    int size;
    heapNode * arr;
}_heap;
typedef _heap * heap;//MAX heap
#define INDEXh(x) (H->arr[(x)][0])//Handy for acquire index of People by index of Heap
void perlocateDown(heap H,int i)//perlocate down the hole of max heap
{
    int child;
    int * tmp = H->arr[i];
    for(;2*i<=H->size;i=child)
    {
        child = 2*i;
        if(child!=H->size)
        {
            child += comparePerson(PERSON(INDEXh(child+1)), PERSON(INDEXh(child)));
        }
        if(comparePerson(PERSON(INDEXh(child)),PERSON(tmp[0])))
        {
            H->arr[i]=H->arr[child];
        }
        else{break;}
    }
    H->arr[i] = tmp;
}
heap buildHeap(int Amin, int Amax)//O(n) = O(Amax-Amin+1) build Heap algorithm by perlocateDown
{
    heap ret;
    ret = (heap)malloc(sizeof(_heap));
    
    int n = 0;
    for(int age=Amin;age<=Amax;age++)
    {
        if(ageCnt[age]){n++;}
    }
    
    ret->size = n;
    ret->arr = (heapNode*)malloc((n+1)*sizeof(heapNode));
    for(int age=Amin;age<=Amax;age++)
    {
        if(ageCnt[age])
        {
            ret->arr[n--] = ageBucket[age];//n,n-1,...,2,1
        }
    }
    for(int i=ret->size/2;i;i--)//O(n) Build heap
    {
        
        perlocateDown(ret, i);
    }
    return ret;
}
void freeHeap(heap H)
{
    free(H->arr);
    free(H);
}

void deleteMax(heap H)//delete Maximum of the heap
{
    H->arr[1] = H->arr[H->size--];
    perlocateDown(H,1);
}
void insertHeap(heap H,heapNode hN)//insert a new heap node into the heap
{
    int i;
    for(i=++H->size;i>=2&&comparePerson(PERSON(hN[0]),PERSON(INDEXh(i/2)));i/=2)//Percolate Up
    {
        H->arr[i]=H->arr[i/2];
    }
    H->arr[i]=hN;//put the new heapNode in the proper position
}

void printQuery(int m,int Amin,int Amax)
{
    heap H = buildHeap(Amin,Amax);
    heapNode tmp;
    if(H->size)
    {
        for(int i=0;i<m;i++)
        {
            printPerson(PERSON(*H->arr[1]));//print Richest person
            
            tmp = ++H->arr[1];//move to the next element of ageBucket

            deleteMax(H);
            
            if(*tmp==-1)//boundary condition, see main()/Bucket Table Sort/create Table
            {
                if(H->size==0){break;}//All ages bucket are empty
            }
            else{insertHeap(H,tmp);}//This age bucket is not empty
        }
    }
    else{printf("None\n");}
    freeHeap(H);
}
/*
 
 50 2
 
 jiiuo 25 1678
 kjpsc 25 -6227
 wwkxd 25 -3127
 cqllh 25 1029
 oxqub 25 -1021
 ikitg 25 1297
 mtwri 25 -3731
 xksuk 25 -3787
 fboxx 25 -7001
 waswn 25 -8628
 vhyqr 25 -8906
 aetpc 25 -9094
 ehtlv 25 -1348
 cehzg 25 -9516
 rxifv 25 7906
 ocuwp 25 5293
 jplwh 25 364
 rpetg 25 -227
 djpbf 25 -8283
 qqflj 25 -1154
 whzia 25 3931
 utpnt 25 5841
 ffqfh 25 -1222
 vnman 25 -4983
 nbjnq 25 -8752
 ogbyi 25 -2211
 rflqo 25 -2170
 jvbug 25 3738
 vbgvq 25 -1814
 tepxc 25 -6450
 bcmov 25 969
 rwspl 25 5296
 haqjf 25 50
 epmts 25 1626
 dvgha 25 4861
 jiavg 25 -6276
 epuya 25 -7128
 vfzxh 25 5825
 huuns 25 5362
 nozvi 25 603
 ykfpj 25 -1433
 baklc 25 9311
 xrmlk 25 -9004
 vbpis 25 9538
 qispg 25 -8830
 pjjmo 25 377
 anepf 25 3090
 hwlab 25 8557
 dxvzh 25 -5317
 ekxga 25 4959

 5 25 25
 50 26 12
 
 */
