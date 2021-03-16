#include <iostream>
#include <vector> 
#include <algorithm>
using namespace std;
vector<int> S;
// 11分,有三个答案错误  
int cmp1(int a, int b){
    return a > b;
} // for non increasing sort 

void init(int n) {
    int i ;
    for(i = 1; i <= n ;i++){
		S[i] = -1 ;   // 一开始，size都是1 ，没有根、 
	}
}

// if  根是他本身，那就直接返回。否则往上寻找根，  path compression采用递归的方法。 
int Find(int x){
	if(S[x] <= -1)  //如果是根那就返回 
		return x;
	return S[x] = Find(S[x]);
}
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
/*0. 每个社交圈的结点号是人的编号，而不是课程。课程是用来判断是否处在一个社交圈的。
1. course[t]表示任意一个喜欢t活动的人的编号。如果当前的课程t，之前并没有人喜欢过，
那么就course[t] = i，i为喜欢course[t]当前人的编号
如果1号喜欢3号活动，那就course【3】 = 1； 

2. course[t]是喜欢t活动的人的编号，
那么findFather(course[t])就是喜欢这个活动的人所处的社交圈子的根结点，
合并根结点和当前人的编号的结点i。即Union(i, findFather(course[t]))，把它们处在同一个社交圈子里面

3. isRoot[i]表示编号i的人是不是它自己社交圈子的根结点，
如果等于0表示不是根结点，如果不等于0，每次标记isRoot[findFather(i)]++，那
么isRoot保存的就是如果当前是根结点，那么这个社交圈里面的总人数
4. isRoot中不为0的编号的个数cnt就是社交圈圈子的个数
最后遍历一遍看每个人是否 
5. 把isRoot从大到小排列，输出前cnt个，就是社交圈人数的从大到小的输出顺序
*/
int main(void){
	vector<int> isRoot;
	int people,i,nob,j,tmphob;
	char ch;
	int course[1010] ={ 0 };// at most 1000 hobbies init 
	cin >> people;
	S.resize(people+1);
	init(people);
	isRoot.resize(people+1);
	for(i = 0; i < people;i ++){
		cin  >> nob;  
		cin >> ch ;
	//	cout << i << S[i] << nob << "开始新一行输出"<< endl ;
		for(j = 0; j < nob ;j++){
			cin >> tmphob;
		//		cout << i << S[i] << course[tmphob] ;
			if(course[tmphob] == 0 ) {
				course[tmphob] = i; // 记录喜欢course[t]当前人的编号
			}
			else{
				//union this person and find[course[tmphob]]
				Union(i,Find( course[tmphob]  )   );
			}
		}
	}
	int count = 0,k = 0;
	// 输出总共几个簇,然后每个簇多少人.  再遍历一遍每个人，看看他们分属于那个集合，并给相应集合的人数+1
	for(i = 1; i <= people;i ++)
		isRoot[Find(i)] ++;
	for(i = 1; i <= people;i ++){
		if(isRoot[i] != 0)      //如果是根
			 count++;
	}
	cout <<  count  <<endl;//iterator可以改元素值,但const_iterator不可改
	sort(isRoot.begin(), isRoot.end(),cmp1);//默认升序,降序需要自己编写一个比较函数来实现，接着调用三个参数的sort：sort(begin,end,compare)就成了。
	//对于list容器，这也可以.  或者用greater<data-type>() 
	cout << isRoot[k++] ;
	while(isRoot[k]){  
	cout << ' '<< isRoot[k++] ; 
	}
} 
