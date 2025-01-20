#include <iostream>
using namespace std;
int S[10010];




// if  根是他本身，那就直接返回。否则往上寻找根，  path compression采用递归的方法。 
int Find(int x){
	if(S[x] <= -1)  //如果是根那就返回 
		return x;
	return S[x] = Find(S[x]);
}
//  
//  如果根不相等那就合并， size小的连接到size大的。 
void Union(int x1,int x2){
	int root1,root2;
	root1 = Find(x1);  //先找到节点的根 
	root2 = Find(x2);
	if( root1 == root2 )
		return ;   //root isn't equal then we merge them
	if(S[root1] < S[root2]){
		S[root1]  += S[root2];
	//	cout  << S[root1] << S[root2] ;
		S[root2] = root1;
	//	cout  << root1 ;
	}
	else{
		S[root2]  += S[root1];
	//	cout  << S[root1] << S[root2] ;
		S[root1] = root2;
	}
}

int main(void){
	int n,i,c1=0,c2=0 ;
	char op;
	cin >> n;
	for(i = 1; i <= n ;i++){
		S[i] = -1 ;   // 一开始，size都是1 ，没有根、 
	}
	for(i = 1 ;i <= n; i++)
    {
   //     printf("%d ",S[i]);
    }
	cin >>  op ;
	while(op != 'S'){
		cin >> c1 >> c2 ;
	//	printf("this line %d%d\n",c1,c2);
		if(op == 'I'){
		//	cout << "union begin"; 
			Union(c1,c2);
		}
		else{
			if( Find(c1) == Find(c2) )
			 	cout << "yes" << endl;
			else
				cout << "no" << endl;
		}
	//		cout << "thisline finded" << endl;
		cin >> op;
	}
	int count = 0 ;
	for(i = 1;i<= n;i++){
		if(Find(i) == i){
			count++;
		}
	} 
	if(count == 1)
		cout << "The network is connected." << endl;
	else 
		cout << "There are "<< count <<" components." << endl;
}
