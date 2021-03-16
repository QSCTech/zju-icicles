#include <stdio.h>
#include <stdlib.h>
#define ERROR 1e8
typedef int ElementType;
typedef enum { push, pop, end } Operation;
// for DS homework stack
typedef struct StackRecord *Stack;
struct StackRecord  {
    int Capacity;       /* maximum size of the stack array */
    int Top1;           /* top pointer for Stack 1 */
    int Top2;           /* top pointer for Stack 2 */
    ElementType *Array; /* space for the two stacks */
};

Stack CreateStack( int MaxElements );
int IsEmpty( Stack S, int Stacknum );
int IsFull( Stack S );
int Push( ElementType X, Stack S, int Stacknum );
ElementType Top_Pop( Stack S, int Stacknum );

Operation GetOp();  /* details omitted */
void PrintStack( Stack S, int Stacknum ); /* details omitted */

int main()
{
    int N, Sn, X;
    Stack S;
    int done = 0;

    scanf("%d", &N);
    S = CreateStack(N);
    while ( !done ) {
        switch( push ) {
        case push: 
            scanf("%d %d", &Sn, &X);//first argument is stacknum, second is input num 
            if (!Push(X, S, Sn)) printf("Stack %d is Full!\n", Sn);
            break;
        case pop:
            scanf("%d", &Sn);
            X = Top_Pop(S, Sn);
            if ( X==ERROR ) printf("Stack %d is Empty!\n", Sn);
            break;
        case end:
            //PrintStack(S, 1);
            //PrintStack(S, 2);
            done = 1;
            break;
        }
    }
    return 0;
}

/* Your function will be put here */


Stack CreateStack( int MaxElements ){
	Stack p=(Stack)malloc(sizeof(struct StackRecord));
    p->Array=(int*)malloc(MaxElements*sizeof(int));
	p->Capacity = MaxElements ;
	p->Top1 = 0;
	p->Top2 = MaxElements - 1;
	return p;
}

 
int IsEmpty( Stack S, int Stacknum ){
	if(Stacknum == 1){
		if(S->Top1 == -1) return  1;
		else return 0;
	}
	else if(Stacknum == 2){
		if(S->Top2 == S->Capacity) return  1;
		else return 0;
	}
	else return 0 ; 
}
int IsFull( Stack S ){
	if(S->Top1>= S->Top2)	return 1;
	else return 0;
}

int Push( ElementType X, Stack S, int Stacknum ){
	if(IsFull(S) == 1) return 0;
	if(Stacknum == 1)  S->Array[S->Top1++] = X;
	else if(Stacknum == 2){
	S->Array[S->Top2--] = X;
	}
	else return 0;
}
ElementType Top_Pop( Stack S, int Stacknum ){
	if(IsEmpty(S , Stacknum) == 1) return ERROR;
	if(Stacknum == 1) return  S->Array[S->Top1--] ;
	else if(Stacknum == 2){
    	return S->Array[S->Top2++] ;
	}
	else	return ERROR;
}
