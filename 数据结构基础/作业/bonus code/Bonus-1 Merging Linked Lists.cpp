#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    int first;
	int Next;
};

int BuildNode(int Lh,struct Node node[],struct Node L1[]) {
	int count = 0;
    while(Lh != -1){
		L1[count] = node[Lh]; 
		printf("node[Lh] = %d , %d , %d \n",node[Lh].first,node[Lh].Element,node[Lh].Next);
		Lh = node[Lh].Next;
		count ++;
    }
    return count;
}

List Merge(List List1,List List2){
}

void print(int bigerSize,int reverSize,struct Node L1[],struct Node L2[]){
	int i =1;
	printf("%05d %d",L1[0].first,L1[0].Element);
	for(i=1; i<bigerSize;i++){
		printf(" %05d\n%05d %d",  L1[i].first,  L1[i].first,  L1[i].Element);
		if(i % 2 == 1 && reverSize >= 0){
			printf(" %05d\n%05d %d",  L2[reverSize].first,  L2[reverSize].first,  L2[reverSize].Element);
			reverSize--;
		}
	}
	printf(" -1");
	
}

int main(){
	int L1h,L2h,N ,size1,size2,bigerSize,reverSize;
	struct Node L1[100]; 
	struct Node L2[100];
	struct Node node[123456];
	int addr[100],data[100],Next[100];
	scanf("%d%d%d", &L1h,&L2h,&N);
	int i = 0,j =0,count = 0;
	for(i = 0; i < N; i++ ){
		scanf("%d", &j);
		node[j].first = j;
		scanf("%d%d",&node[j].Element,&node[j].Next);
		printf("j= %d\n,node[j].element = %d\n,[j].next = %d\n",j,node[j].Element,node[j].Next);
	}
	size1 = BuildNode(L1h,node,L1);
	size2 = BuildNode(L2h,node,L2);
	printf("size1 = %d\n size2 = %d \n L1h= %d  L2h = %d\n",size1,size2,L1h,L2h); 
	
	if(size1>size2){
		bigerSize = size1;
		reverSize = size2 - 1;
		print(bigerSize,reverSize,L1,L2);
	}
	else{
		bigerSize = size2;
		reverSize = size1 - 1;
	    print(bigerSize,reverSize,L2,L1);
	}
	return 0;
}

