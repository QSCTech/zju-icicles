### 1.1 For a graph, if each vertex has an even degree or only two vertexes have odd degree, we can find a ==cycle== that visits every edge exactly once

NO

> It has to be a Euler Cycle, thus only if each vertex has even degrees
>
> Euler Circuit -> exact 2 vertices have odd degrees / all vertices have even degrees

### 1.2 After the first run of Insertion Sort, it is possible that no element is placed in its final position.

YES

> Example: 3 2 1
>
> After first run: 2 3 1



### 2.1 Apply DFS to a directed acyclic graph, and output the vertex before the end of each recursion. The output sequence will be:

A.unsorted

B.topologically sorted

C.reversely topologically sorted

D.None of the above

递归的顺序是遍历1->遍历2->遍历3->.....->遍历n->返回n->返回n-1...->返回3->返回2->返回1

返回的时候打印，因此是从最后一个结点开始打印到源点。是逆拓扑序。

### 2.2 Graph G is an undirected completed graph of 20 nodes. Is there an Euler circuit in G? If not, in order to have an Euler circuit, what is the minimum number of edges which should be removed from G?

Each Node has exactly 19 degrees 

* Euler Circuit (Strong Form) requires every node to be even degrees

* Euler Tour (Weak Form) requires 0 or 2 odd degrees 

**Remove 1 edge, every 2 nodes will lose 1 degrees, so we lose 10 edges**



### 2.3 ![image-20211206121918233](https://s2.loli.net/2021/12/06/1UVoOErQqSYJ3L4.png)

C: should be 5,1,3,6,2,4 (回退按层级，6访问完之后应该是V3层级，然后V1层级)



### 2.4 Use simple insertion sort to sort 10 numbers from non-decreasing to non-increasing, the possible numbers of comparisons and movements are:

The number of comparisons won’t be larger than 45



### 2.5 Given a sorted file of 1000 records. To insert a new record by insertion sort with binary search, the maximum number of comparisons is:

Log2(1000) = 10



