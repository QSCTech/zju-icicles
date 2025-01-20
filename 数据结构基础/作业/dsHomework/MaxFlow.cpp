#include<iostream>
#include<unordered_map>
#include<vector>
#include<string.h>
#include<queue>
#define INT_MAX 99999
using namespace std;
struct Edge{//边类
    int from,to,cap,flow;
    Edge(int f,int t,int c,int fl):from(f),to(t),cap(c),flow(fl) {}  // 构造方法 
};
unordered_map<string,int>trans;//将字符串转换为数字，由0开始编号
vector<Edge>edges;//储存边
vector<int>graph[1005];//整个图，其中graph[i][j]表示结点i的第j条边在edges数组中的序号

void insertEdge(string &from, string &to, int cap) {//插入边，起点为from，终点是to，容量为cap
    if(trans.find(from) == trans.end()){
        trans.insert({from,trans.size()});// give "from" an id = trans.size
    }
    if(trans.find(to) == trans.end()){
        trans.insert({to,trans.size()}); //same as from
    }
// create edge in the vector edges and graph
    int f,t;
    f = trans[from];
    t = trans[to];
    graph[f].emplace_back(edges.size());
    edges.emplace_back(Edge(f,t,cap,0));
    graph[t].emplace_back(edges.size());
    edges.emplace_back(Edge(t,f,0,0));//error C2065: “edges”: undeclared. I don't know wh
}

int MaxFlow(int s,int t){//最大流算法,s为源点,
    int ap[1005],gp[1005];//a数组表示源点到结点a[i]的残量,p数组表示最短路树上到达结点p[i]的边在edges数组中的序号
    int flow=0;//最大流量
    while(true){
        memset(ap,0,sizeof(ap));//将源点到达每个结点的残量初始化为0
        //广度优先遍历查找从源点到达汇点的增广路
        queue<int>q;
        q.push(s);//先把source push进去, source 广度优先搜索, 先遍历从source出发的第一条边.
        ap[s]=INT_MAX;//起点的残量置为无穷大
        while(!q.empty()){
            int v1=q.front();//front() 返回第一个元素(队顶元素)
            cout<< "v1 = "<<v1<<endl;
			q.pop();
            for(int i:graph[v1]){//遍历以x为起点的边 for (int j:i) { //这里i 是数组，j不是下标了，j是来接受每一个数组i遍历出来的值的。
                Edge&e=edges[i];
                if(ap[e.to]==0&&e.cap>e.flow){//当前边的终点的残量为0且容量大于流量
                    gp[e.to]=i;//记录到达该终点的边的编号
                    ap[e.to]=min(ap[v1],e.cap-e.flow);//更新源点到该终点的残量
                    q.push(e.to);//压入队列
                    cout<<i<<"= i  edge[i] = "<<edges[i].to<<"ap[i]="<<ap[i]<<endl;
                }
            }
            if(ap[t]!=0)//终点的残量不为零，跳出循环
                break;
        }
        //清空了之后,再判断
        //a数组表示源点到结点a[i]的残量
        if(ap[t]==0)//源点到终点的残量为零，表示不存在增广路了，跳出外层死循环
            break;
        //
        for(int u=t;u!=s;u=edges[gp[u]].from){//从汇点向前遍历增广路经，更新每条增广路的流量
            edges[gp[u]].flow+=ap[t];//更新这条边的流量和反流量.
            edges[gp[u]^1].flow-=ap[t];//其实就是如果是偶数变奇数?奇数变偶数? 
            //我们可以直观的发现，如果是一个偶数^1,那么答案是偶数+1.如果是一个奇数^1,那么答案是奇数-1
        }
        flow+=ap[t];//增加最大流量
        //再研究从
    }
    return flow;
}

int main(){
    string from,to;
    int n,cap;
    cin>>from>>to;
    cin>>n;
    trans[from]=0;
    trans[to]=1;
    while(n--){
        cin>>from>>to>>cap;// use cin >>string will error in clion because I use include<string.h>,change to <string> can solve it
        insertEdge(from,to,cap);
    }
    printf("%d",MaxFlow(0,1));
    return 0;
}