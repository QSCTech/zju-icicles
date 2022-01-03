其他题目：https://blog.csdn.net/qq_43733499/article/details/103930590

1-1 In a weighted undirected graph, if the length of the shortest path from `b` to `a` is 12, and there exists an edge of weight 2 between `c` and `b`, then the length of the shortest path from `c` to `a` must be no less than 10.

>  True, if it’s less than 10, the shortest path from b to a would be <=9+2=11<12

1-2 Let P be the shortest path from S to T. If the weight of every edge in the graph is incremented by 2, P will still be the shortest path from S to T.

<img src="/Users/naoyuki/Downloads/IMG_541B21FD211B-1.jpeg" alt="IMG_541B21FD211B-1" style="zoom:50%;" />

### 2-2![image-20211116231752734](https://i.loli.net/2021/11/16/MRnIpEaH71f38o9.png)

### 2-3 If besides finding the shortest path from `S` to every other vertices, we also need to count the number of different shortest paths, we can modify the Dijkstra algorithm in the following way: add an array `count[]` so that `count[V]` records the number of different shortest paths from `S` to `V`. Then `count[V]` shall be initialized as:

S won’t be visit after the first compute, since no one is smaller than 0.

