#include <stdio.h>
#include <stdlib.h>
//拓扑排序，是对一个有向无环图(Directed Acyclic Graph简称DAG)G进行拓扑排序，是将G中所有顶点排成一个线性序列，使得图中任意一对顶点u和v，若边(u,v)∈E(G)，则u在线性序列中出现在v之前。
//通常，这样的线性序列称为满足拓扑次序(Topological Order)的序列，简称拓扑序列
// 将传进来的数组用一个队列保存，然后依次出队，出队的顶点必定是 入度为0的顶点，若入度不为0，直接返回false。
// 队列空了之后 还没有返回 false 就说明 能够构成 一个拓扑序列。 
// 他的思路：遍历图，统计所有的点的入度数，然后将案例入队，出队的时候判断入度数是不是0，不是0，就直接返回false。
// 我的思路：遍历邻接链表，如果每一层的后面的节点在样例中出现在层数数字前面，直接返回false。
//然后遍历邻接链表，查询每个节点的邻接节点，判断是否
//含有Seq[i]，如果含有证明Seq[i]入度不为零，则不是拓扑序列。 
typedef enum {false, true} bool;
#define MaxVertexNum 10  /* maximum number of vertices题目中的MaxVertexNUm在测试过程中是会改变的 */
typedef int Vertex;      /* vertices are numbered from 1 to MaxVertexNum */
//Vertedx 就是int  
typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;//firstedge指向的是邻接表的第二个元素
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{   //有顶点, 边和 相邻链表. 
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;//Note: Although the vertices are numbered from 1 to MaxVertexNum, they are indexed from 0 in the LGraph structure.

LGraph ReadG(); /* details omitted 输入的顶点是从 0 开始存放的
例如： 1 被放在 0 位置， 2 被放在 1位置， 3被放在 2 位置… i 被放在 i-1 个位置上。*/

bool IsTopSeq( LGraph Graph, Vertex Seq[] );

int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    scanf("%d", &N);
    for (i=0; i<N; i++) {
        for (j=0; j<G->Nv; j++)
            scanf("%d", &Seq[j]);
        if ( IsTopSeq(G, Seq)==true ) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}

/* Your function will be put here 

*/
 
bool IsTopSeq( LGraph Graph, Vertex Seq[] ){
	int save[MaxVertexNum];
	int rear = 0;
	int i , j , k;
	for (j = 0; j < MaxVertexNum; j++){
		Seq[j]--; 
		save[j] = 0 ;
	}
		
	PtrToAdjVNode p;
		// 遍历每个点 
    //for遍历输出的序列.  seq[i] -- ;for遍历 图的链表, 用while循环 一个个找下去. 
    for( i = 0; i < Graph->Nv; i++){
        for(k = 0; k < Graph->Nv; k++){
            if(save[k] || k == Seq[i])
                continue;  //如果判断过了就跳过, 或者是和自己. 
            else
            {
                p = Graph->G[k].FirstEdge;    
                while(p){
                    if(p->AdjV == Seq[i])  // 如果有入度指向Seq[i],那就错误. 
                        return false;
                    p = p->Next;
                }
            }    
        }
	    save[Seq[i]] = 1; 
    }
	// input degree = 0
	return true;
}


LGraph ReadG()
{
	
    int i,j;
    LGraph LG = (LGraph)malloc(sizeof(struct GNode));
	for(j=0;j<10;j++)
		LG->G[j].FirstEdge=NULL;
    scanf("%d %d", &LG->Nv, &LG->Ne);
    for(i = 0; i < LG->Ne; ++i)
    {
        int p1, p2;
        PtrToAdjVNode adj = (struct AdjVNode *)malloc(sizeof(struct AdjVNode));
        scanf("%d %d", &p1, &p2);
		p1--;p2--;  //注意这里，他输入后都减了1！！！
        adj->AdjV = p2;
        adj->Next = NULL;
        if(LG->G[p1].FirstEdge == NULL)
        {
            LG->G[p1].FirstEdge = adj;
        }
        else
        {
            adj->Next = LG->G[p1].FirstEdge;
            LG->G[p1].FirstEdge = adj;
        }
    }
    return LG;
}
