## 图

学习数据结构, 复杂的数据结构, 去找一个数据可视化的网站, 非常有帮助. 自己也要多画画想想.

### 定义

G::= graph, V = V(G) ::=  finite nonempty set of vertices(顶点), E = E(G) = finite set of edges.

##### 限制:

1. 不用考虑多重边.
2. 不用考虑自循环.(i-> i 是不可能的)

##### 基本术语

完全图 complete graph 

**有最多的边. 边的数量有向图是 n(n-1)  ,无向图是 n(n-1)  /2** 常考

vi -> vj ,  vi is adjacent to vj, vj is adjacent(与…毗连的；邻近的) from vi; 

<vi , vj> is incident(事件) on vi and vj;

联通分量: 

无向图的极大连通子图称为G的**连通分量**( Connected Component)。任何[连通图](https://baike.baidu.com/item/连通图)的连通分量只有一个，即是其自身，非连通的[无向图](https://baike.baidu.com/item/无向图)有多个连通分量。 

连通图: 每一个顶点都是connected.  

强连通图:   有向图每一个顶点互相都有路径到达.

in degree  入度,就是进来的边

out degree 出度, 出去的边

**一个图所有degree 加起来/2 就是总边数e** ,用来推导一些式子.

##### 图的表示

数组法

```c
adj_mat[i][j] = 1 ;    //无向图,adj_mat是对称的,可以存在数组中.
```

链表法  adjacent list

// 有向图可以看出outdegree, 求indegree
//建立一个 反向的lists

adjacent multilists

一条边 数据结构为  {mark, v1,v2}

mark可以用来看这条边有没有统计过

##### 定义

partial order::=  一个precedence relation both 传递而且irreflexive自反.(i-> i 是不可能的)

DAG 图 Directed Acyclic Graph : 有向的非循环图.

topological(拓扑) order:  前置的,在linear order上也是在前面

topological order是不唯一的

**Test an AOV for feasibility, and generate a topological order if possible.**

```c
void Topsort( Graph G )
{   int  Counter;
    Vertex  V, W;
    for ( Counter = 0; Counter < NumVertex; Counter ++ ) {
	V = FindNewVertexOfDegreeZero( );
	if ( V == NotAVertex ) {
	    Error ( “Graph has a cycle” );   break;  }
	TopNum[ V ] = Counter; /* or output V */
	for ( each W adjacent from V )
	    Indegree[ W ] – – ;
    }
}
//T = O( |V|2 )

```

不用每次都搜索一遍,

改进: **Keep all the unassigned vertices of degree 0 in a special box (queue or stack).**

```c
void Topsort( Graph G )
{   Queue  Q;
    int  Counter = 0;
    Vertex  V, W;
    Q = CreateQueue( NumVertex );  MakeEmpty( Q );
    for ( each vertex V )
	if ( Indegree[ V ] == 0 )   Enqueue( V, Q );
 //然后基于队列操作
    while ( !IsEmpty( Q ) ) {
	V = Dequeue( Q );
	TopNum[ V ] = ++ Counter; /* assign next */
	for ( each W adjacent to V )
	    if ( – – Indegree[ W ] == 0 )  Enqueue( W, Q );
    }  /* end-while */
    if ( Counter != NumVertex )
	Error( “Graph has a cycle” );
    DisposeQueue( Q ); /* free memory */
}
//最后所有都在topological sort
```

#### 作业

[数据结构与算法（周测5-最短路径） - nonlinearthink - 博客园 (cnblogs.com)](https://www.cnblogs.com/nonlinearthink/p/11854784.html)

怎么计算至少几个顶点?

A graph with 90 vertices and 20 edges must have at least __ connected component(s).

解法:  让单独的点最多的方法, 是一个20条边的生成树 加上69个顶点, .70个连通分量, 对连通图进行遍历，过程中所经过的边和顶点的组合可看做是一棵普通树，通常称为生成树。

连通图的生成树必须满足以下 2 个条件：

1. 包含连通图中所有的顶点；
2. 任意两顶点之间有且仅有一条通路；



问题二: Given an undirected graph G with 16 edges, where 3 vertices are of degree 4, 4 vertices are of degree 3, and all the other vertices are of degrees less than 3. Then G must have at least __ vertices.

解法 : Sum of vertex degrees 2 number of edges , 16*2 -12 -12 = 8 个顶点,  无向图点的入度是边数量的两倍.



问题三: 判断题 Let P be the shortest path from S to T. If the weight of every edge in the graph is incremented by 2, P will still be the shortest path from S to T. 错

解法: 假如说最短路径上一共有10条边，而另一条路径虽然比最短路径长，但它只有一条边，如果全加1，就会导致边少的路径成为新的最短路径。



问题四: 若要求在找到从S到其他顶点最短路的同时，还给出不同的最短路的条数，我们可以将Dijkstra算法略作修改，增加一个count[]数组：count[V]记录S到顶点V的最短路径有多少条。则count[V]应该被初始化为：

  A.对所有顶点都有count[V]=1
  B.对所有顶点都有count[V]=0
  C.count[S]=1;对于其他顶点V则令count[V]=0
  D.count[S]=0;对于其他顶点V则令count[V]=1

答案为 C , 由于S到S一定有一条长度为0的边，所以初始化为1，其他则是0 .



##### 拓扑序列

拓扑排序，是对一个有向无环图(Directed Acyclic Graph简称DAG)G进行拓扑排序，是将G中所有顶点排成一个线性序列，使得图中任意一对顶点u和v，若边(u,v)∈E(G)，则u在线性序列中出现在v之前。通常，这样的线性序列称为满足拓扑次序(Topological Order)的序列，简称拓扑序列

**Hamiltonian Cycle**

require contains every vertex 顶点, 由指定的起点前往指定的终点，途中经过所有其他节点且只经过一次*/

题目:  有两个奇数度, 其他都是偶数度,  就有欧拉路径  X

还得是连通的 无向图. 

### 最短路径算法

#### single source 最短路径

从0开始找,宽度优先

把距离为0的点都找了.记录下来.

Dijkstra 的算法是一种算法，用于查找图形中两个节点之间的最短距离

Dijkstra’s algorithm (for weighted shortest paths) distance[ u ] = minimal length of path

distance[u1] < distance [u2] , we add u1 into S , S change,calculate distance[u2] again .

因为Dijkstra算法总是在V-S中选择“最轻”或“最近”的顶点插入到集合S中，所以我们说它使用了贪心策略。

```C
for(;;){
	if(V == notAvertex)
	break;

	for(each W adjacent to V)
	if(unknown)
		if(distance smaller)
}
//V = smallest unknown distance vertex ;
```

#### PAT 1163 Dijkstra Sequence（30）

给出的序列是Dijkstra序列的关键在于，序列的第i个数x的dist[x]是等于当时求到的最短路径。

##### 复杂度

[Dijkstra算法能得出最短路径的最优解，但由于它遍历计算的节点很多，所以效率低。]

所以搜索 Q 中最小元素的运算（Extract-Min(Q)）只需要线性搜索 Q 中的所有元素。
这样的话算法的运行时间是 O(E^2)。

对于边数少于 E^2 的稀疏图来说，我们可以用邻接表来更有效的实现迪科斯彻算法。
同时需要将一个二叉堆或者斐波纳契堆用作优先队列来寻找最小的顶点（Extract-Min）。

当用到二叉堆时候，算法所需的时间为O(( V+E )logE)，
斐波纳契堆能稍微提高一些性能，让算法运行时间达到O(V+ElogE)。

we have a  min -heap 
update small 
// method 1: DecreaseKey -O(log|V|)
good if graph is sparse , don't have too much edges

// method 2 : 
//  must keep doing deleteMin until an unknown vertex emerges.
insert W in priority queue repeatly .
requires 

pairing heap and Fibonnacci heap could improve it.

### Network Flow Problem

参考https://blog.csdn.net/u014679804/article/details/47016513

#### （**流网络**）

G=(V, E)是一个有向图，图中每条边(u, v) ∈E有一个非负的容量值c(u, v) ≥ 0。
 并且如果边集合E包含一条边(u, v)，则图中不存在反方向的边(v, u)。
 如果(u, v) ∉ E，定义c(u, v) = 0，且图中不允许自循环。
 两个特殊结点：源结点s和汇点t。每个结点都在从源结点到汇点的某条路径上。即对于每个结点v∈V，流网络包含一条路径s -> v -> t。
 因此，流网络是连通的，且由于源节点外每个结点都至少有一条进入的边，则|E| ≥ |V| -1。

增广路径p为残留网络Gf中从s到t的一条简单路径。根据残留网络的定义，在不违反容量限制的条件下，G中所对应的增广路径上的每条边(u,v)可以容纳从u到v的某额外正网络流。
而能够在这条路径上的网络流的最大值一定是p中边的残留容量的最小值。

在最大流问题中，我们意在寻找一个带权有向图**G**中从一个特定的源点**s**到一个特定的汇点**t**的最大流。

寻找最大流有几种不同的算法，包括Ford Fulkerson算法，Edmonds Karp算法和Dinic算法。

最大流的对偶问题是最小割

#### 最小割问题

定义：找到一个最小capacity的 cut。

也就是在寻找图**G**的最大**s-t**流的同时找到图**G**的最小**s-t**割，也就是为了使图**G**中**s**和**t**不连通所需要移除的权重最小的边的集合。

这时候(1,2)和(3,4)边上的流量都等于容量了，我们再也找不到其他的增广路了，当前的流量是1。
但这个答案明显不是最大流，因为我们可以同时走1-2-4和1-3-4，这样可以得到流量为2的流。
那么我们刚刚的算法问题在哪里呢？问题就在于我们没有给程序一个”后悔”的机会，应该有一个不走(2-3-4)而改走(2-4)的机制。那么如何解决这个问题呢？回溯搜索吗？那么我们的效率就上升到指数级了。
而这个算法神奇的利用了一个叫做反向边的概念来解决这个问题。即每条边(I,j)都有一条反向边(j,i)，反向边也同样有它的容量。

#### 残留网络

  a.在给定的流网络G=(V,E)中，设f为G中的一个流，并考察一对顶点u，v∈V，在不超过容量c(u,v)的条件下，从u到v之间可以压入的额外网络流量，就是(u,v)的残留容量，就好像某一个管道的水还没有超过管道的上限，那么就这条管道而言，就一定还可以注入更多的水。
残留容量的定义为：cf(u,v)=c(u,v)-f(u,v)。而由所有属于G的边的残留容量所构成的带权有向图就是G的残留网络。

  残留网络中的边既可以是E中边，也可以是它们的反向边。只有当两条边(u,v)和(v,u)中，至少有一条边出现在初始网络中时，边(u,v)才会出现在残留网络中。

#### 流网络的算法

1. 速度慢，复杂度为O(mf*E)的Ford Fulkerson算法，

   ```pesudo
   initMaxFlow
   
   while there is an augmenting path
   
     find an augmenting path using DFS
   
     for each edge u->v in the path
   
       decrease capacity u->v by bottleneck
   
       increase capacity v->u by bottleneck
   
     increase maxflow by bottleneck
   ```

   在Ford-Fulkerrson方法的每次迭代中，寻找某条增广路径p，
   然后使用p来对流f进行修改（增加）。我们不断地在图中寻找增广路径，并依据来增大f的值，直到图中不含增广路径。

   在第一次找到增广路之后，在把路上每一段的容量减少delta的同时，也把每一段上的反方向的容量增加delta

2. 复杂度为O(V*E^2)的Edmonds Karp算法，或者

3. 复杂度为O(V^2*E)的Dinic算法

### 最小生成树MST

spanning tree , 

顶点是原来图的顶点, 边是原来边的子集. 它连接所有顶点与最小边缘数，具有最小可能的重量，没有cycle。由于此图不包含cycle，因此**它被称为树。**

#### note:

1.  图是连通的 
2. spanning tree包含所有的顶点, 至少有n-1条边

#### 生成方法

##### 贪婪法

Prim's 算法, O(**E** log **V**) greedy MST algorithm that grows a Minimum Spanning Tree from a starting source vertex until it spans the entire graph.

 implement Prim's algorithm with two well-known data structures:

1. A Priority Queue PQ ([Binary Heap](https://visualgo.net/zh/heap) or just use C++ STL priority_queue/Java PriorityQueue), and
2. A Boolean array of size **V** (to decide if a vertex has been taken or not, i.e. in the same connected component as source vertex **s** or not).

With these, we can run Prim's Algorithm in O(**E** log **V**) because we process each edge once and each time, we call **Insert((w, v))** and **(w, v) = ExtractMax()** from a PQ in O(log **E**) = O(log **V2**) = O(2 log **V**) = O(log **V**). As there are **E** edges, Prim's Algorithm runs in O(**E** log **V**).

##### Kruskal 算法, maintain a forest

An O(**E** log **V**) greedy MST algorithm that grows a forest of minimum spanning trees and eventually combine them into one MST.

多个MST, 再合成一个MST

Kruskal's algorithm first sort the set of edges **E** in non-decreasing weight (there can be edges with the same weight), and if ties, by increasing smaller vertex number of the edge, and if still ties, by increasing larger vertex number of the edge.

ties是啥意思?

加进去会形成cycle ,就不能加. 循环结束后, 边 < 顶点数 -1 . 就说没有 spanning tree , 说明 图 是非连通的. 

```pesudo
Sort E edges by increasing weight

T = {}

for (i = 0; i < edgeList.length; i++)

  if adding e = edgelist[i] does not form a cycle

    add e to T

  else ignore e

MST = T 
```

PAT顶级 1016 Uniqueness of MST (35分)（最小生成树唯一性判断）
思路：

1.用并查集实现kruskalkruskal算法，
最后查询一共有几个集合即可完成判断图是否联通以及计算不连通状况下有几块连通分量的工作；

2.根据kruskal算法的贪心思想，我们每次考虑未使用过的边里权值最小的那一条边，如果这条边两边的端点不属于同一集合，就合并它们。那这种思想里什么时候会出现不唯一性呢？即你当前遍历的这条边可以联通两个集合，我在未遍历的边里有权值相等的边也联通这两个集合，当且仅当此时会产生不唯一性；