//
// Created by 12638 on 2020/12/11.

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );
#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices
/*
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */

typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

/*
void PrintV( Vertex V )
{
    printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

/* Your function will be put here */
//void StronglyConnectedComponents(Graph G, void(*visit)(Vertex V));

void StronglyConnectedComponents(Graph G, void (*visit)(Vertex)) {
    int IsConnect[MaxVertices][MaxVertices] = {0 };
    int i = 0 , j;
    //先对每个结点dfs, 记录在矩阵中
    for (; i < G->NumOfVertices; i++) {
        IsConnect[i][i] = 1;//和自己连通
        int isread[MaxVertices] = { 0 };
        int t = 0 ;
        int stack[MaxVertices];
        stack[++t] = i;//结点入栈
        //dfs 栈非空 ,那就搜索每一个结点, 然后dfs 每一个结点, 然后回溯,标记他们.
        while (t) {
            j = stack[t--];
            //pop出栈
            PtrToVNode tempNode ; // 搜索每一个结点
            tempNode = G->Array[j];//按这个结点搜索
            for(;tempNode;tempNode =tempNode->Next){
                IsConnect[i][tempNode->Vert] = 1;
                if(isread[tempNode->Vert] == 0 ){
                    isread[tempNode->Vert] = 1;
                    stack[++t] = tempNode->Vert ;  //push
                }
                //搜索时，把当前搜索树中未处理的节点加入一个堆栈， 回溯时可以判断栈顶到栈中的节点是否为一个强连通分量。
            }
            //当前结点没有出度 ,开始回溯
        }
    }
   // printf(" finished\n");
    int a[MaxVertices] = {0 };
    for (i = 0;i < G->NumOfVertices;) {
        int j;
        for (j = i; j < G->NumOfVertices; j++) {
            if (IsConnect[i][j]  && IsConnect[j][i]) {
                a[j] = 1;
                //如果是第一个,那就print
                (*visit)(j);//这是一个函数指针,自动打印
            }
        }
        printf("\n");
        // 已经打印过, 就直接过
        //printf(" jump up\n");
        while (a[i] ) {
            i++;
            if (i > G->NumOfVertices)
                break;
        }
    }
}

//

