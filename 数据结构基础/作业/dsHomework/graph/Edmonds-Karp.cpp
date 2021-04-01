/*
本题是PAT上顶级1003，考察的知识点其实只有一个，最大流问题。
用基于广度优先搜索的Edmonds-Karp算法求解。题目意思就是说求解最多能从地球站发送出去的最大人数，
在到达目的星球（MAR）上途径每一个行星（不包括MAR）上都没有收留多余游客的能力，到达的游客必须运送出去。
那么可以将EAR视为源点s，MAR视为汇点，是一个单源点单汇点的最大流问题。代码如下：
https://blog.csdn.net/richenyunqi/article/details/86756528
*/
#include<bits/stdc++.h>
using namespace std;
struct Edge{//边类
    int from,to,cap,flow;
    Edge(int f,int t,int c,int fl):from(f),to(t),cap(c),flow(fl) {}
};
unordered_map<string,int>trans;//将字符串转换为数字，由0开始编号
vector<Edge>edges;//储存边
vector<int>graph[1005];//整个图，其中graph[i][j]表示结点i的第j条边在edges数组中的序号
int a[1005],p[1005];//a数组表示源点到结点a[i]的残量,p数组表示最短路树上到达结点p[i]的边在edges数组中的序号
void insertEdge(string&from,string&to,int cap){//插入边，起点为from，终点是to，容量为cap
    if(trans.find(from)==trans.end())//将起点转换为数字编号
        trans.insert({from,trans.size()});
    if(trans.find(to)==trans.end())//将终点转换为数字编号
        trans.insert({to,trans.size()});
    int f=trans[from],t=trans[to];//获取起点、终点的数字编号
    graph[f].push_back(edges.size());//在图中插入该边
    edges.push_back(Edge(f,t,cap,0));
    graph[t].push_back(edges.size());//在图中插入该边的反向边
    edges.push_back(Edge(t,f,0,0));
}
int MaxFlow(int s,int t){//最大流算法,s为源点,t为汇点
    int flow=0;//最大流量
    while(true){
        memset(a,0,sizeof(a));//将源点到达每个结点的残量初始化为0
        //广度优先遍历查找从源点到达汇点的增广路
        queue<int>q;
        q.push(s);
        a[s]=INT_MAX;//起点的残量置为无穷大
        while(!q.empty()){
            int x=q.front();
            q.pop();
            for(int i:graph[x]){//遍历以x为起点的边
                Edge&e=edges[i];
                if(a[e.to]==0&&e.cap>e.flow){//当前边的终点的残量为0且容量大于流量
                    p[e.to]=i;//更新到达该终点的边的编号
                    a[e.to]=min(a[x],e.cap-e.flow);//更新源点到该终点的残量
                    q.push(e.to);//压入队列
                }
            }
            if(a[t]!=0)//终点的残量不为零，跳出循环
                break;
        }
        if(a[t]==0)//终点的残量为零，表示不存在增广路了，跳出外层死循环
            break;
        for(int u=t;u!=s;u=edges[p[u]].from){//从汇点向前遍历增广路经，更新每条增广路的流量
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
        }
        flow+=a[t];//增加最大流量
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
