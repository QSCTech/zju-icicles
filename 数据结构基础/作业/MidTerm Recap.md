### Time Complexity:

```c++
void func ( int n )
{   int i, j;
    for (i=n; i>0; i/=3)
        for (j=0; j<i; j+=2)
            printf("%d ", i+j);
}
```

This is a sum of array problem（等比数列）. It’s actually a linear steps.

### A graph with 50 vertices and 17 edges must have at most ____ connected component(s).

The most cases are, the edges are all in a single large component. Then the rest each vertex can form a component.

50 Vertices and 17 Edges, 43+1. 

n(n-1)/2 >= 17 -> N=7. #Components = 50-43+1



### How many distinct topological sequences are there in the following DAG？

![image-20211123092917247](https://i.loli.net/2021/11/23/3qNfzHeZE9myibO.png)

使用常规的indegree算法，然后出现多个indegree为0的情况时分类讨论

### Suppose that enqueue is allowed to happen at both ends of a queue, but dequeue can only be done at one end. If elements are enqueued in the order {a, b, c, d, e}, the impossible dequeue sequence is:

同样进行模拟，dbcae不可能

因为abcde入queue，那在d被pop之前，abc肯定还在队列中，且由于单边出队列，所以abcd的顺序是确定的，顺序为dbca

但是以abcd的顺序入队列，无论如何都实现不了dbca的情况

### Push and pop { 23, 17, 13, 53, 11, 7, 29 } sequentially into then out of a stack. Suppose that each number is pushed into a queue right after it gets out of the stack, and the dequeue sequence is { 23, 13, 7, 11, 53, 29, 17 }. If both the stack and the queue are initially empty, then the minimum size of the stack must be:

直接模拟，相当于pop sequence，不断push,遇到queue sequence相同的就不断pop直到不相同，最大情况是17,53,11,7的时候，答案是4