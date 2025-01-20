/*
������PAT�϶���1003�������֪ʶ����ʵֻ��һ������������⡣
�û��ڹ������������Edmonds-Karp�㷨��⡣��Ŀ��˼����˵�������ܴӵ���վ���ͳ�ȥ�����������
�ڵ���Ŀ������MAR����;��ÿһ�����ǣ�������MAR���϶�û�����������ο͵�������������οͱ������ͳ�ȥ��
��ô���Խ�EAR��ΪԴ��s��MAR��Ϊ��㣬��һ����Դ�㵥������������⡣�������£�
https://blog.csdn.net/richenyunqi/article/details/86756528
*/
#include<bits/stdc++.h>
using namespace std;
struct Edge{//����
    int from,to,cap,flow;
    Edge(int f,int t,int c,int fl):from(f),to(t),cap(c),flow(fl) {}
};
unordered_map<string,int>trans;//���ַ���ת��Ϊ���֣���0��ʼ���
vector<Edge>edges;//�����
vector<int>graph[1005];//����ͼ������graph[i][j]��ʾ���i�ĵ�j������edges�����е����
int a[1005],p[1005];//a�����ʾԴ�㵽���a[i]�Ĳ���,p�����ʾ���·���ϵ�����p[i]�ı���edges�����е����
void insertEdge(string&from,string&to,int cap){//����ߣ����Ϊfrom���յ���to������Ϊcap
    if(trans.find(from)==trans.end())//�����ת��Ϊ���ֱ��
        trans.insert({from,trans.size()});
    if(trans.find(to)==trans.end())//���յ�ת��Ϊ���ֱ��
        trans.insert({to,trans.size()});
    int f=trans[from],t=trans[to];//��ȡ��㡢�յ�����ֱ��
    graph[f].push_back(edges.size());//��ͼ�в���ñ�
    edges.push_back(Edge(f,t,cap,0));
    graph[t].push_back(edges.size());//��ͼ�в���ñߵķ����
    edges.push_back(Edge(t,f,0,0));
}
int MaxFlow(int s,int t){//������㷨,sΪԴ��,tΪ���
    int flow=0;//�������
    while(true){
        memset(a,0,sizeof(a));//��Դ�㵽��ÿ�����Ĳ�����ʼ��Ϊ0
        //������ȱ������Ҵ�Դ�㵽���������·
        queue<int>q;
        q.push(s);
        a[s]=INT_MAX;//���Ĳ�����Ϊ�����
        while(!q.empty()){
            int x=q.front();
            q.pop();
            for(int i:graph[x]){//������xΪ���ı�
                Edge&e=edges[i];
                if(a[e.to]==0&&e.cap>e.flow){//��ǰ�ߵ��յ�Ĳ���Ϊ0��������������
                    p[e.to]=i;//���µ�����յ�ıߵı��
                    a[e.to]=min(a[x],e.cap-e.flow);//����Դ�㵽���յ�Ĳ���
                    q.push(e.to);//ѹ�����
                }
            }
            if(a[t]!=0)//�յ�Ĳ�����Ϊ�㣬����ѭ��
                break;
        }
        if(a[t]==0)//�յ�Ĳ���Ϊ�㣬��ʾ����������·�ˣ����������ѭ��
            break;
        for(int u=t;u!=s;u=edges[p[u]].from){//�ӻ����ǰ��������·��������ÿ������·������
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
        }
        flow+=a[t];//�����������
    }
    return flow;
}
int main(){
    string from,to;
    int n,cap;
    cin>>from>>to>>n;
    trans[from]=0;
    trans[to]=1;
    while(n--){
        cin>>from>>to>>cap;
        insertEdge(from,to,cap);
    }
    printf("%d",MaxFlow(0,1));
    return 0;
}
