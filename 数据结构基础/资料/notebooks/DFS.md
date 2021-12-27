# DFS的应用

```cpp
visited[V] = true;
for(each W adjacent to V){
    if(!visited[W])
        DFS(W);
}
```

## 双连通性biconnectivity

一个双连通component is a maximal biconnected subgraph

1 去掉后不再连通, 那1就是割点ariticulation point.

#### 找到双连通component 

Using depth first search to obtain a spanning tree of G

随意从某一个顶点开始, 



back edge

## 判断是否是割点

note : if u is an ancestor of v, then Num(u) < Num(v).

root is 割点 , <=> 他有at least 两个孩子

其他vertex u是一个割点, <=> u  has at least 1 child. and 不可能 move down 至少一步 and jump up to u的祖先. 

或者  u  has at least 1 child 并且low(child) >= num(u)

##### low的定义

 计算一个low  ,back回去最小的值是多少.就是在DFS的过程中，如果当前节点是极大强联通子图的话，他的根节点的标号就是对应的LOW值：如下图 **LOW[4]= min(LOW[4], num[1])** 

![](https://images2017.cnblogs.com/blog/1322166/201801/1322166-20180120183011115-1431772847.jpg)

**再回溯到节点1，更新 LOW[1]的值： LOW[1]= min(LOW[1], LOW[3])  值还是为1**

可以直接返回到root, low就是1 .　

num的值是编号的. 就是DFS的顺序.



LOW［］作为每个点在这颗树中的，最小的子树的根，每次保证最小，like它的父亲结点的时间戳这种感觉。如果它自己的LOW［］最小，那这个点就应该从新分配，变成这个强连通分量子树的根节点。

num  == low 说明他是这个分量的根结点. 比如6是它本身这个子树的根

spinning tree 生成每个low 的值, 然后判断是否是割点.

```cpp
try all vertex u, if u hasnt been visited, DFS(u)

DFS(u), initiate num[u] = low[u] = DFSCount

  try all neighbor v of u

    if v is free, DFS(v)

      low[u] = min(low[u], low[v])

      check the condition

    else low[u] = min(low[u], num[v])
```

## Euler circuits

一笔画问题,

### Euler tour , 欧拉通路一笔画完

刚好有两个是奇数的,

### Euler circuit欧拉图  一笔画完并且结束在起点

每个顶点有偶数个度



可以用一个链表记录路径, 一个指针指向最后scanned的边.

T = O(|E|+|V|)  , 边全部一遍, 顶点不止一遍

Hamiliton cycle是一个NP问题

### 作业题: 

#### 一

Apply DFS to a directed acyclic graph, and output the vertex before the end of each recursion. The output sequence will be:

答案:深度优先遍历算法中,退栈次序是逆拓扑有序。DFS入栈顺序是入度为0的顶点入栈，然后将与此顶点相连的弧度删除，继续将入度为0的顶点入栈，删除对应的弧，重复此过程！

#### 二

 DFS sequence  就是入栈,再一步步出栈, 出栈一个, 看看有没有别的没有遍历过的.

Graph G is an undirected completed graph of 20 nodes. Is there an Euler circuit in G? If not, in order to have an Euler circuit, what is the minimum number of edges which should be removed from G?

思路: 完全图是一个简单的无向图，其中每对不同的顶点之间都恰连有一条边相连。

`19+18+...+3+3  = (3+19)*16 /2 = 8*22 +3  = 179` 

#### 代码补全: 

Write a program to find the strongly connected components in a digraph. 

https://www.cnblogs.com/shadowland/p/5872257.html

Tarjan算法是基于对图深度优先搜索的算法，每个强连通分量为搜索树中的一棵子树。搜索时，把当前搜索树中未处理的节点加入一个堆栈，回溯时可以判断栈顶到栈中的节点是否为一个强连通分量。

再Tarjan算法中，有如下定义。

DFN[ i ] : 在DFS中该节点被搜索的次序(时间戳)

LOW[ i ] : 为i或i的子树能够追溯到的最早的栈中节点的次序号

当DFN[ i ]==LOW[ i ]时，为i或i的子树可以构成一个强连通分量。

先DFS, 然后 回溯时发现LOW[ 5 ]==DFN[ 5 ] ,  LOW[ 6 ]==DFN[ 6 ] ,则{ 5 } , { 6 } 为两个强连通分量。回溯至3节点，拓展节点4.

拓展节点1 ， 发现1在栈中更新LOW[ 4 ]，LOW[ 3 ] 的值为1

可以发现，运行Tarjan算法的过程中，每个顶点都被访问了一次，且只进出了一次堆栈，每条边也只被访问了一次，所以该算法的时间复杂度为**O(N+M)**。

### 拓扑排序

对一个有向无环图(Directed Acyclic Graph简称DAG)G进行拓扑排序，是将G中所有顶点排成一个线性序列，使得图中任意一对顶点u和v，若边<u,v>∈E(G)，则u在线性序列中出现在v之前。通常，这样的线性序列称为满足拓扑次序(Topological Order)的序列，简称拓扑序列。简单的说，由某个集合上的一个偏序得到该集合上的一个全序，这个**操作称之为拓扑排序**。



若图G有环，则G不存在拓扑排序序列。 √ 

若图G为连通图且不存在拓扑排序序列，则图G必有环。 √

拓扑序一定是唯一的。 ×   不一定唯一 

