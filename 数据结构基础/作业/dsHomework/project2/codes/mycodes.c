#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX(a,b) (a>b)?a:b

//Dijkstra ÿ����Ŀǰ��ԭ������ĵ㣬���м���������ͬ�Ļ�ȡ����һ��������ʵ�ȼ�����⼸����Ҳ�� 
// distance save the distance from the node to root;
const int INF = 0x3fffffff;// min��¼��Сֵ, һ��ʼ����Ϊ���.  
int Nv, G[1010][1010] = {0}, distance[1010], query[1010];
int Dijkstra(int root){
    int i,min = INF, j,tmp;
    for(i = 0;i< 1010;i++){
    	distance[i] = INF; //һ��ʼ�����е������Ϊ���. 
	}
	int log[1010] = {0};// ���еĵ㶼û�б�����. 
	distance[root] = 0; // ԭ�㵽ԭ��ľ�����0 
	//printf("init finished \n");
	for(i = 0; i < Nv; i++){  //�����ѯ��ÿ���㶼û�����Ǿͷ���1 
		min = INF;//һ��ʼ��̾�����Ϊ���. 
	//	printf("begin find min \n");
		for(j = 1;j <= Nv;j++){
			if(log[j] == 0 && distance[j] < min){	//���û������, ���ҵ�ԭ��ľ������ 
				min = distance[j];			//�Ǿ͸��� ��̾��� 
		//		printf("%d\n",min);
			}
		}
//		printf("search min finished\n");//�����ѯ�Ľڵ�query[i]��ԭ��ľ�����min
//		printf("min = %d j = %d Nv = %d query[0] = %d\n",min,j,Nv,query[i]);//query[i] ,Nv���û������. 
		// Nv  =5 is correct, query[0] = 5  is correct ,
		if(distance [query[i]]  == min ){  // �����ѯ�ĵ�,��̾����������ҵ�����̾���. 
			tmp = query[i] ; //��¼�²�ѯ�ĵ� 
	//		printf("%d\n",tmp);
		}
		else{
			return 0; //�� query ����Ҫ��� Dijkstra sequence������ false
		}
		//������Ѿ������. ������ 0 ��1�����, 1 ��ʾ�ǹ��� static vis[1001] 
		if(!log[tmp]){
			log[tmp] = 1 ;// ��������,��¼Ϊ1  
		}
	//	printf("begin update distance\n");
		// û�б����������&& ������� &&�������ԭ�����> ������ѯ�ڵ�+��ѯ�ڵ㵽ԭ�����
		//����ÿһ����㵽ԭ��ľ��� 
		for(j = 1 ; j < Nv+1;j++){
			if( log[j] == 0   &&  G[tmp][j] != 0 && distance[j] > distance[tmp] + G[tmp][j]    ){
				distance[j] = distance[tmp] + G[tmp][j];  	//update distance from j to root;
		//		printf("%d\n",j);
			}
		}
	}
	return 1 ;//�����ѯ��ÿ���㶼û�����Ǿͷ���1 
}
int main(){
    int  Ne, v,u, distance, K,i,j,judge;
   scanf("%d%d", &Nv, &Ne);//���붥�����ͱ��� 
//    Nv = 5, Ne = 7;//��ʼ��һЩֵ������� 
//G[1][2] = G[2][1] = 2;
//G[1][5] = G[5][1] = 1;
//G[2][3] = G[3][2] = 1;
//G[2][4] = G[4][2] = 1;
//G[2][5] = G[5][2] = 2;
//G[3][5] = G[5][3] = 1;
//G[3][4] = G[4][3] = 1;
    for (i = 0; i < Ne; i++){  //����ÿ���ߵĴ�С 
        scanf("%d%d%d", &u, &v, &distance);//������� 
        G[u][v] = G[v][u] = distance;// ͼ��û��[0][0]�� 
    }
    scanf("%d",&K);//�����ѯ������ 
	for (i = 0; i < K; i++){ //��ѯK�� 
        for (j = 0; j < Nv; j++) { //ÿ�������Nv��,Ҳ���Ƕ��� ���� 
			scanf("%d", &query[j]);//�����ѯ��ÿ���� 
    	}
		judge = Dijkstra(query[0]); // ����ԭ�� 
        printf("%s\n", judge ? "Yes" : "No");//judgeΪ1�����yes ,Ϊ0���no 
    }
    return 0;
}
