//
// Created by 12638 on 2020/12/7.
//
/*
#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include<queue>
using namespace std;

struct Edge{
    int from,to,cap,flow;
    Edge(int f,int t, int c, int fl):from(f),to(t),cap(c),flow(fl){}//creator
};
/*
本题是PAT上顶级1003，考察的知识点其实只有一个，最大流问题。vector定义时出现error C2065: “q”: 未声明的标识符 复制过来的时候,要把unix的RF变成window的CRLF.
用基于广度优先搜索的Edmonds-Karp算法求解。题目意思就是说求解最多能从地球站发送出去的最大人数，
在到达目的星球（MAR）上途径每一个行星（不包括MAR）上都没有收留多余游客的能力，到达的游客必须运送出去。
那么可以将EAR视为源点s，MAR视为汇点，是一个单源点单汇点的最大流问题
*/
//unordered_map<string,int>trans;//将字符串转换为数字，由0开始编号
//vector<Edge>edges;
//vector<int>graph[1005];//整个图，其中graph[i][j]表示结点i的第j条边在edges数组中的序号

/*
1. 首先把所有残余网络初始化为0,广度优先遍历查找从源点到达汇点的增广路
然后定义一个数组 a,a[i]代表从源点到i的最大流通量，即每次源点开始搜索，
最后的a[n]就是从源点到汇点的最大流通量，
 首先把source 入队, source 广度优先搜索, 先遍历从source出发的第一条边.
 起点的残量置为无穷大
2.遍历x节点的每一条边.如果当前边的终点的残量为0且容量大于流量,
那么更新最短路上到达结点p[i]的边在edges数组中的序号, p中记录终点在graph中的序号
 更新源点到该终点的残量, 再把终点压入队列继续判断从这个点出发的所有边,
 直到终点的残量不为零或者没有终点在队列中.
 3.一次搜索结束后, 源点到终点的残量a[t]为零，表示不存在增广路了，跳出外层死循环
 否则从汇点向前遍历增广路经，更新每条增广路的流量, p[u]偶数变奇数?奇数变偶数?
 flow记录最大流量
 4. 继续循环搜索, 再把将源点到达每个结点的残量初始化为0,再把source push进去.
在每一次搜索完成之后，如果a[n]==0，说明已经没有剩余可以流通的量了，then break and 直接return.
 */
/*
int MaxFlow(int s, int t) {//最大流算法,s为源点,
    int ap[1005],gp[1005];//a数组表示源点到结点a[i]的残量,p数组表示最短路树上到达结点p[i]的边在edges数组中的序号
    //edges < 500 , we need 1005 gp because it is a directed graph
    int flow = 0;//最大流量
    while(1){
        //init the augmenting path
        for(int i = 0;i < 1005;i++){
            ap[i] = 0;
        }
        queue<int>q;  //广度优先遍历查找从源点到达汇点的增广路
        q.emplace(s);      //from source we begin search
        ap[s]  = INT_MAX;  // 源点到自己的残量 = max
        while(!q.empty()){
            int v1 = q.front(); //vector 1 = source //遍历以队列第一个元素为起点的边
            //     cout<< "v1 = "<<v1<<endl;
            q.pop();
            // graph[s] 是一个vector,  vector里面的数字表示v1连着的一些vertex; 我们把每个vertex取出来判断一下.
            for(int i:graph[v1]){//遍历以x为起点的边 for (int j:i) { //这里i 是数组，j不是下标了，j是来接受每一个数组i遍历出来的值的。
                Edge &e = edges[i];
                if (ap[e.to] == 0 && e.cap > e.flow) {  //如果当前边的终点的残量为0且边的容量大于流量, 说明这个新的边可以增大他的残量.
                    gp[e.to] = i ;   // i is the number in graph 记录到达该终点的边的编号
                    ap[e.to] = min(ap[v1], e.cap - e.flow) ;  //更新源点到该终点的残量, 是原点到v1距离这一段路径流量和容量-流量残余流量的较小值
                    q.emplace(e.to);        //把终点压入队列,继续判断从这个点出发的所有边,   //     直到终点的残量不为零或者没有终点在队列中.
                    //          cout << i << "= i  edge[i] = " << e.to << "ap[i]=" << ap[i] << endl;
                }
            }
            if(ap[t])//终点的残量不为零，跳出循环
                break;
        }
        //清空了队列之后,再判断
        //ap数组表示源点到结点a[i]的残量 在每一次搜索完成之后，如果==0，说明已经没有剩余可以流通的量了，直接跳出外层死循环 then return
        if(!ap[t])//源点到终点的残量为零，表示不存在增广路了，跳出外层死循环
            break;
        //否则, 往前找,更新每一个边的流量和反流量
        //其实就是如果是偶数变奇数?奇数变偶数?
        for(int i = t;i != s; i =edges[gp[i]].from){
            edges[gp[i]].flow += ap[t];
            // this process can update reversal flow
            edges[(gp[i] % 2 == 0 ? gp[i] + 1 : gp[i] - 1)].flow -= ap[t];
        }
        flow += ap[t];
        //4. 继续循环搜索, 再把将源点到达每个结点的残量初始化为0,再把source push进去,
    }
    return flow;
}
*/
/*插入边，起点为from，终点是to，容量为cap ,
首先找找这个边在不在无序map, 如果不在 ,那就insert一个 , 通过tran的size,就可以获得他的大小
then , we could use creator 构造函数, 在edges中创建边.  同时在 graph图中插入边,以及初始化一个反向边.
insertEdge
 */
/*
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
    edges.emplace_back(Edge(t, f, 0, 0));//error C2065: “edges”: undeclared. I don't know wh
}
*/