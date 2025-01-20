#include <iostream>
#include <vector> 
#include <algorithm>
using namespace std;
vector<int> S;
// 11��,�������𰸴���  
int cmp1(int a, int b){
    return a > b;
} // for non increasing sort 

void init(int n) {
    int i ;
    for(i = 1; i <= n ;i++){
		S[i] = -1 ;   // һ��ʼ��size����1 ��û�и��� 
	}
}

// if  �����������Ǿ�ֱ�ӷ��ء���������Ѱ�Ҹ���  path compression���õݹ�ķ����� 
int Find(int x){
	if(S[x] <= -1)  //����Ǹ��Ǿͷ��� 
		return x;
	return S[x] = Find(S[x]);
}
//  �����������Ǿͺϲ��� sizeС�����ӵ�size��ġ� 
void Union(int x1,int x2){
	int root1,root2;
	root1 = Find(x1);  //���ҵ��ڵ�ĸ� 
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
/*0. ÿ���罻Ȧ�Ľ������˵ı�ţ������ǿγ̡��γ��������ж��Ƿ���һ���罻Ȧ�ġ�
1. course[t]��ʾ����һ��ϲ��t����˵ı�š������ǰ�Ŀγ�t��֮ǰ��û����ϲ������
��ô��course[t] = i��iΪϲ��course[t]��ǰ�˵ı��
���1��ϲ��3�Ż���Ǿ�course��3�� = 1�� 

2. course[t]��ϲ��t����˵ı�ţ�
��ôfindFather(course[t])����ϲ�����������������罻Ȧ�ӵĸ���㣬
�ϲ������͵�ǰ�˵ı�ŵĽ��i����Union(i, findFather(course[t]))�������Ǵ���ͬһ���罻Ȧ������

3. isRoot[i]��ʾ���i�����ǲ������Լ��罻Ȧ�ӵĸ���㣬
�������0��ʾ���Ǹ���㣬���������0��ÿ�α��isRoot[findFather(i)]++����
ôisRoot����ľ��������ǰ�Ǹ���㣬��ô����罻Ȧ�����������
4. isRoot�в�Ϊ0�ı�ŵĸ���cnt�����罻ȦȦ�ӵĸ���
������һ�鿴ÿ�����Ƿ� 
5. ��isRoot�Ӵ�С���У����ǰcnt���������罻Ȧ�����ĴӴ�С�����˳��
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
	//	cout << i << S[i] << nob << "��ʼ��һ�����"<< endl ;
		for(j = 0; j < nob ;j++){
			cin >> tmphob;
		//		cout << i << S[i] << course[tmphob] ;
			if(course[tmphob] == 0 ) {
				course[tmphob] = i; // ��¼ϲ��course[t]��ǰ�˵ı��
			}
			else{
				//union this person and find[course[tmphob]]
				Union(i,Find( course[tmphob]  )   );
			}
		}
	}
	int count = 0,k = 0;
	// ����ܹ�������,Ȼ��ÿ���ض�����.  �ٱ���һ��ÿ���ˣ��������Ƿ������Ǹ����ϣ�������Ӧ���ϵ�����+1
	for(i = 1; i <= people;i ++)
		isRoot[Find(i)] ++;
	for(i = 1; i <= people;i ++){
		if(isRoot[i] != 0)      //����Ǹ�
			 count++;
	}
	cout <<  count  <<endl;//iterator���Ը�Ԫ��ֵ,��const_iterator���ɸ�
	sort(isRoot.begin(), isRoot.end(),cmp1);//Ĭ������,������Ҫ�Լ���дһ���ȽϺ�����ʵ�֣����ŵ�������������sort��sort(begin,end,compare)�ͳ��ˡ�
	//����list��������Ҳ����.  ������greater<data-type>() 
	cout << isRoot[k++] ;
	while(isRoot[k]){  
	cout << ' '<< isRoot[k++] ; 
	}
} 
