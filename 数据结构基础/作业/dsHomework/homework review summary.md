# 考试复习

### homework 1

1. The major task of algorithm analysis is to analyze the time complexity and the space complexity. √ 

2. The Fibonacci number sequence {F*N*} is defined as: *F*0=0, *F*1=1, F*N*=F*N−1*+F*N−2*, *N*=2, 3, .... The time complexity of the function which calculates *F**N* recursively is Θ(*N*!).    X

3. 递归方程：T(n) = 3*T(n/3) + 1, n>1, T(1) = 1

应该是3的log N 次方, 时间复杂度为 N. 

### homework 2

1. For a sequentially stored linear list of length *N*, the time complexities for deleting the first element and inserting the last element are *O*(1) and *O*(*N*), respectively.    X 

 a sequentially stored linear list of length ,顺序存储的线性表支持随机存取，所以查询的时间是常数时间，但插入需要把后面每一个元素的位置都进行调整，所以是线性时间。 插入最后一个时间为O(1).

2. If a linear list is represented by a linked list, the addresses of the elements in the memory must be consecutive(连续的). X 

3.  循环队列, 不能 rear == front. 队列满时rear == front -1. enqueue时rear增加, dequeue front 增加.

#### HW 3

Push 5 characters `ooops` onto a stack. In how many different ways that we can pop these characters and still obtain `ooops`?

答案: 123  , 132, 231, 213, 321. 五种,  312 是不行的. 



#### HW4 tree

There exists a binary tree with 2016 nodes in total, and with 16 nodes having only one child.  X 

n0+n1+n2 =2016=1+0n0+1n1+2n2  根结点不是任何结点的孩子, 

发现除不尽. 

选择题的话,可以 画一个出来,然后看看.

It is always possible to represent a tree by a one-dimensional integer array 对的

中序二叉树 = 后序普通树



#### HW5 binary search tree

In a binary search tree which contains several integer keys including 4, 5, and 6, if 4 and 6 are on the same level, then 5 must be their parent. X

不是能有两个5, 而是可以很高.



#### HW6

根据前序遍历为第一个, 然后找到中序遍历中的点,分成两块.

 选择题6

If a binary search tree of *N* nodes is complete, which one of the following statements is FALSE?

答案: C 选项 the maximum key must be at a leaf node.

complete是**除最后一层外其他层均充满**不是*全部充满*.



#### HW 8:

1. 不连通, 35个边. 

答案: 至少10个顶点, 从3个点开始往上加,找规律即可.

2. In a connected graph, the number of edges must be greater than the number of vertices minus 1. X 可以等于

3. A graph with 90 vertices and 20 edges must have at least __ connected component(s).   答案70,  20个 两边连, 50个没边

4. If graph G is NOT connected and has 35 edges, then it must have at least ____ vertices  答案:  5个边 ,3+3+4 = 10 , 6个边, 15,7个, 21, 8个 28, 9个 , 35 . 加一个点, 就是10个点. 

5. Given the adjacency list of a directed graph as shown by the figure. There is(are) __ strongly connected component  . 两边都有是强连通分量. 有向图的极大强连通子图，称为强连通分量 . 有更大的要选大的.



#### HW11

 Apply DFS to a directed acyclic graph, and output the vertex before the end of each recursion. The output sequence will be:

答案: reversely topologically sorted



#### HW 12

堆排序 extra space 复杂度为O(1);

#### HW13

题一If there are less than 20 inversions in an integer array, the Quick Sort will be the best method among Quick Sort, Heap Sort and Insertion Sort. 错的.  数组长度越大, 快排效果越好.

题二Among the following sorting methods, which ones will be slowed down if we store the elements in a linked structure instead of a sequential structure?

1 Insertion sort; 2. Selection Sort; 3. Bubble sort; 4. Shell sort; 5. Heap sort

答案: D Shell sort;  Heap sort是在数组中, heap本身在数组中, shell sort也是在数组中. 链表查询较慢,

题三 During the sorting, processing every element which is not yet at its final position is called a "run". Which of the following cannot be the result after the second run of quick sort?

A. 5, 2, 16, 12, 28, 60, 32, 72

B. 2, 16, 5, 28, 12, 60, 32, 72

C. 2, 12, 16, 5, 28, 32, 72, 60

D. 5, 2, 12, 28, 16, 32, 72, 60

答案: D 三个pivot , 快速排序每一轮的过程, 观察有几个元素在正确的位置, 每轮当分割点**pivot的元素一定会在正确的位置**. 最理想的是每次都选到中间值, 这样两轮后有三个分割点,.

A选择 28和72在正确, B选择2和72在正确, 因为选到了最值72,所以是两个pivot. C选择2和28,32在正确.D没有选到最值, 又没有三个pivot, 就是错的.



题四:判断题, During the sorting, processing every element which is not yet at its final position is called a "run". To sort a list of integers using quick sort, it may reduce the total number of recursions by processing the small partition first in each run. X 错误, 我们希望它尽量平均分.处理两个都一样.



#### HW14

The average search time of searching a hash table with *N* elements is:

答案是D  cannot be determined 因为和你的解决方案有很大关系.