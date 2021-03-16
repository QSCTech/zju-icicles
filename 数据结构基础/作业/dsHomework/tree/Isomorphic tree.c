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
    printf(“%d\n”, Isomorphic(T1, T2));
    return 0;
}

/* Your function will be put here */

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};
/*  为空 return 1. 
 是叶了,返回1. 
 否则判断子树 
给根结点, A左 =B左 && A右是否为B右. 如果是,返回1.如果不是返回0.
判断A右  =B左,  &&如果是,A左是否为B右
 A右  !=B左,返回0 ;
 如果分别只有一个,判断是否相等,是的话,返回1. 一个为两个一个为一个,返回0. (包括在上面的==情况) 
如果不等于, 0
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

