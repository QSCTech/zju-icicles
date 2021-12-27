# 堆 笔记

## 方法

找到12 比18小,,
找到15比18小, 把15上移, 
T(N) = log(N)

最大堆  删除最大结点.
最小堆的操作Delete min

首先判断是否为空
minelement = 第一个,lastelemnt= 最后一个

```cpp
void PercolateDown( int p, PriorityQueue H ){
	int tmp = H->Elements[p],child = 2*p;
	while(child < H->Size  ){    //还没有到底 
		// swap child and H[p]
	//		printf(" child = %d\n",child);
		if(  H->Elements[p]  > H->Elements[child]){ 
			if(  H->Elements[child]  > H->Elements[child+1]){//child is median
                H->Elements[p] = H->Elements[child+1];
                p = child+1;
                child = 2*p;
			}
			else{//child is smallest
                H->Elements[p] = H->Elements[child];
                p = child;
                child = 2*p;
			}
		}
		else if( H->Elements[p]  > H->Elements[child+1]){  //right node smaller than parent
		H->Elements[p] = H->Elements[child+1];
		p = child+1;
		child = 2*p;
		} 
		else break;
	}
	H->Elements[p] = tmp;
}
```

找到其他的,就需要所有的都扫描一遍.


插入建堆的时间复杂度为nlgn。

## buildheap

时间复杂度 线性时间,   
$$
2^{h+1} -1 -(h+1)  T(N) =O(N)
$$
不是一个个插入,而是数组不断比较, 最后构建完成.

取前一半,然后下移

堆分为大根堆和小根堆，是完全二叉树。大根堆的要求是每个节点的值都不大于其父节点的值，即A[PARENT[i]] >= A[i]。在数组的非降序排序中，需要使用的就是大根堆，因为根据大根堆的要求可知，最大的值一定在堆顶。
既然是堆排序，自然需要先建立一个堆，而建堆的核心内容是调整堆，使二叉树满足堆的定义（每个节点的值都不大于其父节点的值）。调堆的过程应该从最后一个非叶子节点开始，
假设有数组A = {1, 3, 4, 5, 7, 2, 6, 8, 0}。那么调堆的过程如下图，数组下标从0开始，A[3] = 5开始。分别与左孩子和右孩子比较大小，如果A[3]最大，则不用调整，否则和孩子中的值最大的一个交换位置，
在图1中是A[7] > A[3] > A[8]，所以A[3]与A[7]对换，从图1.1转到图1.2。 
https://blog.csdn.net/lz233333/article/details/61629935
题目2-2 :Using the linear algorithm to build a min-heap from the sequence {15, 26, 32, 8, 7, 20, 12, 13, 5, 19}, and then insert 6. Which one of the following statements is FALSE?

## priority queues的应用

1. 找到第k个最大的

2. 堆排序,之后还会讲

## d heap性质

```
i =(parent-1)d +1+l 
if i%d == 0 
then l = d  
 i =(parent-1)d +1+d  = parent*d +1
p =( i -1) /d 

else then l = i%d
p =( i -1 - i%d+d) /d 
 i =(parent-1)d +1+i%d 
```

