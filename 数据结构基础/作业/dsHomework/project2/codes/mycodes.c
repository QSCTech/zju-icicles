#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX(a,b) (a>b)?a:b

//Dijkstra 每次找目前距原点最近的点，若有几个距离相同的会取其中一个，但其实先检查另外几个点也可 
// distance save the distance from the node to root;
const int INF = 0x3fffffff;// min记录最小值, 一开始设置为最大.  
int Nv, G[1010][1010] = {0}, distance[1010], query[1010];
int Dijkstra(int root){
    int i,min = INF, j,tmp;
    for(i = 0;i< 1010;i++){
    	distance[i] = INF; //一开始到所有点距离置为最大. 
	}
	int log[1010] = {0};// 所有的点都没有遍历过. 
	distance[root] = 0; // 原点到原点的距离是0 
	//printf("init finished \n");
	for(i = 0; i < Nv; i++){  //如果查询的每个点都没问题那就返回1 
		min = INF;//一开始最短距离置为最大. 
	//	printf("begin find min \n");
		for(j = 1;j <= Nv;j++){
			if(log[j] == 0 && distance[j] < min){	//如果没遍历过, 而且到原点的距离更短 
				min = distance[j];			//那就更新 最短距离 
		//		printf("%d\n",min);
			}
		}
//		printf("search min finished\n");//如果查询的节点query[i]到原点的距离是min
//		printf("min = %d j = %d Nv = %d query[0] = %d\n",min,j,Nv,query[i]);//query[i] ,Nv输出没有问题. 
		// Nv  =5 is correct, query[0] = 5  is correct ,
		if(distance [query[i]]  == min ){  // 如果查询的点,最短距离是我们找到的最短距离. 
			tmp = query[i] ; //记录下查询的点 
	//		printf("%d\n",tmp);
		}
		else{
			return 0; //此 query 非所要求的 Dijkstra sequence，返回 false
		}
		//这个点已经查过了. 可以用 0 和1来标记, 1 表示记过了 static vis[1001] 
		if(!log[tmp]){
			log[tmp] = 1 ;// 遍历过了,记录为1  
		}
	//	printf("begin update distance\n");
		// 没有遍历过这个点&& 有这个边 &&如果他到原点距离> 他到查询节点+查询节点到原点距离
		//更新每一个结点到原点的距离 
		for(j = 1 ; j < Nv+1;j++){
			if( log[j] == 0   &&  G[tmp][j] != 0 && distance[j] > distance[tmp] + G[tmp][j]    ){
				distance[j] = distance[tmp] + G[tmp][j];  	//update distance from j to root;
		//		printf("%d\n",j);
			}
		}
	}
	return 1 ;//如果查询的每个点都没问题那就返回1 
}
int main(){
    int  Ne, v,u, distance, K,i,j,judge;
   scanf("%d%d", &Nv, &Ne);//输入顶点数和边数 
//    Nv = 5, Ne = 7;//初始化一些值方便调试 
//G[1][2] = G[2][1] = 2;
//G[1][5] = G[5][1] = 1;
//G[2][3] = G[3][2] = 1;
//G[2][4] = G[4][2] = 1;
//G[2][5] = G[5][2] = 2;
//G[3][5] = G[5][3] = 1;
//G[3][4] = G[4][3] = 1;
    for (i = 0; i < Ne; i++){  //输入每条边的大小 
        scanf("%d%d%d", &u, &v, &distance);//输入距离 
        G[u][v] = G[v][u] = distance;// 图是没有[0][0]的 
    }
    scanf("%d",&K);//输入查询语句个数 
	for (i = 0; i < K; i++){ //查询K次 
        for (j = 0; j < Nv; j++) { //每条语句有Nv个,也就是顶点 个数 
			scanf("%d", &query[j]);//输入查询的每个点 
    	}
		judge = Dijkstra(query[0]); // 传入原点 
        printf("%s\n", judge ? "Yes" : "No");//judge为1就输出yes ,为0输出no 
    }
    return 0;
}
