#include <stdio.h>
#include <stdlib.h>
//���������Ƕ�һ�������޻�ͼ(Directed Acyclic Graph���DAG)G�������������ǽ�G�����ж����ų�һ���������У�ʹ��ͼ������һ�Զ���u��v������(u,v)��E(G)����u�����������г�����v֮ǰ��
//ͨ�����������������г�Ϊ�������˴���(Topological Order)�����У������������
// ����������������һ�����б��棬Ȼ�����γ��ӣ����ӵĶ���ض��� ���Ϊ0�Ķ��㣬����Ȳ�Ϊ0��ֱ�ӷ���false��
// ���п���֮�� ��û�з��� false ��˵�� �ܹ����� һ���������С� 
// ����˼·������ͼ��ͳ�����еĵ���������Ȼ�󽫰�����ӣ����ӵ�ʱ���ж�������ǲ���0������0����ֱ�ӷ���false��
// �ҵ�˼·�������ڽ��������ÿһ��ĺ���Ľڵ��������г����ڲ�������ǰ�棬ֱ�ӷ���false��
//Ȼ������ڽ�������ѯÿ���ڵ���ڽӽڵ㣬�ж��Ƿ�
//����Seq[i]���������֤��Seq[i]��Ȳ�Ϊ�㣬�����������С� 
typedef enum {false, true} bool;
#define MaxVertexNum 10  /* maximum number of vertices��Ŀ�е�MaxVertexNUm�ڲ��Թ������ǻ�ı�� */
typedef int Vertex;      /* vertices are numbered from 1 to MaxVertexNum */
//Vertedx ����int  
typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;//firstedgeָ������ڽӱ�ĵڶ���Ԫ��
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{   //�ж���, �ߺ� ��������. 
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;//Note: Although the vertices are numbered from 1 to MaxVertexNum, they are indexed from 0 in the LGraph structure.

LGraph ReadG(); /* details omitted ����Ķ����Ǵ� 0 ��ʼ��ŵ�
���磺 1 ������ 0 λ�ã� 2 ������ 1λ�ã� 3������ 2 λ�á� i ������ i-1 ��λ���ϡ�*/

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
		// ����ÿ���� 
    //for�������������.  seq[i] -- ;for���� ͼ������, ��whileѭ�� һ��������ȥ. 
    for( i = 0; i < Graph->Nv; i++){
        for(k = 0; k < Graph->Nv; k++){
            if(save[k] || k == Seq[i])
                continue;  //����жϹ��˾�����, �����Ǻ��Լ�. 
            else
            {
                p = Graph->G[k].FirstEdge;    
                while(p){
                    if(p->AdjV == Seq[i])  // ��������ָ��Seq[i],�Ǿʹ���. 
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
		p1--;p2--;  //ע�����������󶼼���1������
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
