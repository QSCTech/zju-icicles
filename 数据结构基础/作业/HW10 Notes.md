### 2-1![image-20211124214000660](https://s2.loli.net/2021/12/27/xitOPyJ3fmYR4BI.png)

(2,3)->(3,5)->(3,4)->(5,6)->(1,2)

### 2-2

The minimum spanning tree of any weighted graph ____

> may not exists
>
> Exists iff the graph is connected

### 2-3:

![image-20211125002104006](https://i.loli.net/2021/11/25/jWxmV1tR7ZTcfrl.png)

老老实实画图，因为min cut很难找，所以只能用ford-fulkerson一步一步算，答案104

虽然这么做少了一次锻炼自己的机会，但是我推荐先做完Universal Traversal Sites，然后直接用那道题的代码来求这道题的答案，或者你可以用那道题的代码作为手算的验证。

### 2-4

Gr中，每条边的双向流量和不变，答案是5.

### 7-1

Universal Traversal Sites 就是求maxflow

* 比较麻烦的地方在于将string转化成int，这样比较graph的操作（当然你也可以在graph的实现上采用unordered_map)

### 7-2

可以用Prim或者Krustal方法求

Krustal法的思想如下：

先用Krustal求出MST，Krustal的过程中也可以顺便把过程中计算出来的MST的edges存到一个array里面

* 每次从图中剔除掉一个计算出来的MST的边，然后对剔除掉的图再求一次Krustal，如果剔除前后结果相同，说明就不是unique的（相当于这条边是可替代的）。
* 如果所有edges都试过一次，发现都不相同，那么就是unique的。
