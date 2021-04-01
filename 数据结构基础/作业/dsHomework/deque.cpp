#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
    PtrToNode Front, Rear;
};
Deque CreateDeque();
int Push( ElementType X, Deque D );
ElementType Pop( Deque D );
int Inject( ElementType X, Deque D );
ElementType Eject( Deque D );

Operation GetOp();          /* details omitted */
void PrintDeque( Deque D ); /* details omitted */

int main()
{
    ElementType X;
    Deque D;
    int done = 0;

    D = CreateDeque();
    while (!done) {
        switch(GetOp()) {
        case push: 
            scanf("%d", &X);
            if (!Push(X, D)) printf("Memory is Full!\n");
            break;
        case pop:
            X = Pop(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case inject: 
            scanf("%d", &X);
            if (!Inject(X, D)) printf("Memory is Full!\n");
            break;
        case eject:
            X = Eject(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case end:
            PrintDeque(D);
            done = 1;
            break;
        }
    }
    return 0;
}

/* Your function will be put here */

Deque CreateDeque(){
	Deque p = (Deque)malloc(sizeof(struct DequeRecord));
    p->Front = (PtrToNode)malloc(sizeof(struct Node));
    p->Front->Last = NULL;
    p->Rear = p->Front;
    p->Rear->Next = NULL;
	return p;
}
int Push( ElementType X, Deque D ){
	PtrToNode p;
    p = (PtrToNode)malloc(sizeof(struct Node));
    if(!p) return 0; //out of memory 
    p->Element = X;
    if(D->Front == D->Rear){ //if no data in deque
    	D->Front->Next = p;
		p->Last  = D->Front;
		D->Rear  = p;
    	D->Rear->Next = NULL;
	}
    else{
    p->Next = D->Front->Next;
    p->Last = D->Front ;
    D->Front->Next->Last = p;
    D->Front->Next = p;//check the TopPointer
	}
	return 1;
}
ElementType Pop( Deque D ){
	PtrToNode p;
	ElementType e;
	if(D->Front == D->Rear){  //judge D->Front是否为null before 取D->Front的next 
        return ERROR;
    } 
	p = D->Front->Next;
	e = D->Front->Next->Element; 
    if(D->Front->Next == D->Rear){ // rear can save data
    	D->Rear = D->Front;
    	D->Rear->Next = NULL;
	}
	else{
        p->Next->Last = D->Front;// Front is a dummy node, Front->Next is the leftest node,
        D->Front->Next = p->Next ;
    }
        free (p);
        return e;
}
int Inject( ElementType X, Deque D ){
	PtrToNode p;
    p = (PtrToNode)malloc(sizeof(struct Node));
    if(!p) return 0; //out of memory 
    p->Element =  X;
    if(D->Front == D->Rear){ //if no data in deque
    	D->Front->Next = p;
		p->Last  = D->Front;
		D->Rear  = p;//as push , for convenient and for init same way
	}
    else{
    D->Rear->Next = p;
    p->Last = D->Rear;
	D->Rear = p ;
	p->Next = NULL;
	}
	return 1;
}
ElementType Eject( Deque D ){
	PtrToNode p;
	ElementType e;
	if(D->Rear == D->Front){ //in fact Rear don't = null because init D->rear = first node 
        return ERROR;
    }
	p = D->Rear;
	e = D->Rear->Element; 
    D->Rear = D->Rear->Last;// Rear is not a dummy node,Rear is the rightest node,
    D->Rear->Next = NULL;
    free(p);
    return e;
}
