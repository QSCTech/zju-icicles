#include<iostream> 
#include<set>
#include<vector>
/* require contains every vertex ����, ��ָ�������ǰ��ָ�����յ㣬;�о������������ڵ���ֻ����һ��*/
using namespace std;

int main() {
		int i=0,j = 0, k = 0,n = 0,N,M,u ,v,q ;
	    cin >> N;
	    cin >> M;
		 // N is number of the  vertices
	    // the number of edges in an undirected graph
	 // �þ����ͼ.
	    int G[N+10][N+10]   = {0};//��̬����ı�׼����
	    for(i = 0;i < M; i++) {
	    	cin >> v; 
	    	cin >> u ;
	    	G[u][v] = G[v][u] = 1 ;
	    }
	    cin >> q; // ��ѯ����
	  
	    bool flag1, flag2;
	    //��ÿ���ʵĵ����һ��vector���棬Ҳ����set�У�����������setȥ�أ���Ϊ��β����ͬ�ģ�
	    //������ɺ��ж�set��С�Ƿ��n��ͬ������ĵ�-1�Ƿ��n��ͬ������β�Ƿ���ͬ�������һ�㲻���㣬��ʹflag1λfalse
	    //for����ÿ�����ڽӵ㣬��������ڽӵ�û��ͨ·��flag2��Ϊfalse
	    //����flag��Ϊtrue�����no
	    //each describes an edge in the format Vertex1 Vertex2, where the vertices are numbered from 1 to N
	    for(j = 0;j < q;j++) {
	    	//�µĲ�ѯ
	    	vector<int> vec ; //���ͱ����ǰ�װ������,�������ǻ�������,�����������͵�����,��ʼ��һ��sizeΪ0��vector
	  	    set<int> set ;
	    	flag1 = flag2 = true ;
	    	cin >> n ; // ��n����
	    	int t;
	    	//input this query 
	    	for(k = 0; k < n; k++) {
	    		cin >> t;
	    		set.insert(t);//set don't duplicate.
	    		vec.insert(vec.end(),t);
	    	}
	    //	vector<int>::iterator ite = vec.begin();
//	for (; ite != vec.end(); ite++){
//		cout << *ite;
//	}
//	cout << endl;
	    	 //cout << vec.end() << vec.begin() << vec.size() << set.size() <<endl;  
	    	// if the not a loop or size not equal to n  vector.size -1 ��Ϊ��β���ظ���,
	    	if(set.size() !=  N ||  vec.size()-1  != N || vec[0] !=  vec[k-1] ){  //vec[n-1] �ᱨ��.Ҫ��.elementAt(index) 
	    		flag1 = false; 
	    	}
	    	
	    	for(i = 0; i < n-1; i++) {
	    		if(G[ vec[i]]  [vec[i+1]] == 0 )// don't have edge
	    			flag2 = false;
	    	}
	    	
	   // 	cout <<  flag1 << flag2  << endl;  
	    	if(flag1 && flag2)
	    		cout << "YES" <<endl;
	    	else
	    		cout << "NO"  <<endl;
	    	
	 	    set.clear();
		}
}
//�������������,����������1,Ϊɶ�ǶԵ���?  


