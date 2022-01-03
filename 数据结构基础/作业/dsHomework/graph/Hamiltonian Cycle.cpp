#include<iostream> 
#include<set>
#include<vector>
/* require contains every vertex 顶点, 由指定的起点前往指定的终点，途中经过所有其他节点且只经过一次*/
using namespace std;

int main() {
		int i=0,j = 0, k = 0,n = 0,N,M,u ,v,q ;
	    cin >> N;
	    cin >> M;
		 // N is number of the  vertices
	    // the number of edges in an undirected graph
	 // 用矩阵存图.
	    int G[N+10][N+10]   = {0};//动态数组的标准分配
	    for(i = 0;i < M; i++) {
	    	cin >> v; 
	    	cin >> u ;
	    	G[u][v] = G[v][u] = 1 ;
	    }
	    cin >> q; // 查询条数
	  
	    bool flag1, flag2;
	    //将每次问的点存在一个vector里面，也插入set中，这样可以用set去重，因为首尾是相同的，
	    //输入完成后判断set大小是否和n相同且输入的点-1是否和n相同，且首尾是否相同，如果有一点不满足，就使flag1位false
	    //for遍历每两个邻接点，如果两个邻接点没有通路，flag2设为false
	    //两个flag都为true就输出no
	    //each describes an edge in the format Vertex1 Vertex2, where the vertices are numbered from 1 to N
	    for(j = 0;j < q;j++) {
	    	//新的查询
	    	vector<int> vec ; //泛型必须是包装类类型,而不能是基本类型,包括基本类型的数组,初始化一个size为0的vector
	  	    set<int> set ;
	    	flag1 = flag2 = true ;
	    	cin >> n ; // 有n个边
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
	    	// if the not a loop or size not equal to n  vector.size -1 因为首尾是重复的,
	    	if(set.size() !=  N ||  vec.size()-1  != N || vec[0] !=  vec[k-1] ){  //vec[n-1] 会报错.要用.elementAt(index) 
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
//第五个测试用例,经过了两次1,为啥是对的呢?  


