#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};

Tree BuildTree(); /* details omitted */

int Isomorphic( Tree T1, Tree T2 );

int main()
{
    Tree T1, T2;
    T1 = BuildTree();
    T2 = BuildTree();
    printf(��%d\n��, Isomorphic(T1, T2));
    return 0;
}

/* Your function will be put here */

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};
/*  Ϊ�� return 1. 
 ��Ҷ��,����1. 
 �����ж����� 
�������, A�� =B�� && A���Ƿ�ΪB��. �����,����1.������Ƿ���0.
�ж�A��  =B��,  &&�����,A���Ƿ�ΪB��
 A��  !=B��,����0 ;
 ����ֱ�ֻ��һ��,�ж��Ƿ����,�ǵĻ�,����1. һ��Ϊ����һ��Ϊһ��,����0. (�����������==���) 
���������, 0
*/ 
int Isomorphic( Tree T1, Tree T2 ){
	if(T1 == NULL && T2 == NULL){
		return 1;
	} 
	else if (T1 == NULL ||  T2 == NULL ) {
		return 0;
	}
	else {
		if (T1->Element != T2->Element){
			return 0 ;
		} 
		else {
			if(T1->Left == NULL &&T1->Right == NULL && T1->Left == NULL &&T1->Right == NULL){
				return 1;
			}
			else{
				return	 Isomorphic( T1->Left, T2->Left )&&Isomorphic( T1->Right, T2->Right ) || Isomorphic( T1->Left, T2->Right )&&Isomorphic( T1->Right, T2->Left ) ;
			} 
		}

	}
}

