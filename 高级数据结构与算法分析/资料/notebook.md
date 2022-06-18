第一节课

维护一个完全二叉树, 时间复杂度太大，所以需要平衡树。 保证最坏情况也是logn。

hl - hr 绝对值小于1 , 那就叫平衡树.   

### AVL树

平衡的BST. 

lemma : 一个平衡二叉树有n个节点, must have height lgn.

 左旋转, 右旋转 ，可以 在O1时间内保留BST的性质. 

插入怎么恢复平衡?  修复最低的不平衡的点即可

哪些节点的平衡会出问题?    只有到root路径上的节点会出问题

最低的不平衡的点, 左右子树高度差是2 . 

L case u节点左边比右边高2 , R case 反之.  v节点就是高的那个子树的root. 

 sibling 是兄弟姐妹的意思。

##### LL case

v节点左边h+1 高, 右边 h高,u节点不平衡, 就把u改成v的右节点. 

##### LR case

v节点右边h+1 高, 左边 h高,u节点不平衡. 这里就要v节点右边的w, 做一次左旋, 再做一次右旋. 就是让w左节点为v, 右节点为u.  

##### LL case特点

u的左子树高度>右子树高度，v的左子树高度>=右子树高度

##### RR case特点

 u的右子树高度>左子树高度，v的右子树高度>=左子树高度

##### 删除

- **被删除节点的空缺应该如何填补**

1. 如果被删除节点是叶子节点，则不需要填补空缺
2. 而如果是枝干节点，则需要填补空缺，理想的情况是使用某个节点填补被删除节点的空缺后，整棵树仍然保持平衡
   a) 如果节点的左右子树有一棵为空，则使用**非空子树**填补空缺
   b) 如果节点的左右子树均为非空子树，则u有两个children,  先和右边子树最左边的叶节点互换,然后删掉叶子, 

删除如果导致不平衡, 不可能是变矮, 两个子树高度一个减一一个不变, 不变的在删除前更高.

恢复可能变矮, 可能不变. 

边更新高度边修复平衡

但是如果仍然按照插入时的方法来判断不平衡，则会发现，`节点v`的左右子树高度一致，即在满足了`L`后，后续无法判断这种情况属于哪种范型

对于`R`方向也是一样

本文称它们为`L型`和`R型`

不过这两种情况的处理也很简单，实际上当出现这种情况时，使用`LL型`或`LR型`的调整方法**均可以**达到使树重新平衡的目的

homework 

If the depth of an AVL tree is 6 (the depth of an empty tree is defined to be -1), then the minimum possible number of nodes in this tree is: 33  因为一开始不是0 是-1 

## 第二节课

### 红黑树

1. 每个节点红色或者黑色
2. 根是黑色
3. leaf 是nil 黑色
4. red node 的children一定是黑色
5. 每个node 到叶子, 包含的黑色节点数量一定相同. 

#### 插入节点

插入为红色 node v,  父节点为u

##### case1 

u的sibling 是红,  那么 u和sibling都染黑, u的父节点染红. 

### B+树

order = M 

fanout就是children的个数

性质: 

1.  M>= root 的fanout >=2 , 除非root是叶子节点
2.   M>= internal node 的fanout >= ceil(M/2)
3. M>=叶子的key(data pointer) >= ceil(M/2) ( 除非leaf是root)
4. 所有叶子必须在同一层,不符合时考虑把parent往下拉一层

#### 删除

删除叶子, 向上修改索引.

如果小于 ceil(M/2):

如果sibling 有超过ceil(M/2): 借一个

如果sibling 只有ceil(M/2): 合并

都要向上修改索引

#### 分裂

internal node 中间节点 >= order, 叶节点> order, 就要分裂,  

比如把中间的值

#### 2-3树

参考：[浅谈算法和数据结构: 八 平衡查找树之2-3树](https://www.cnblogs.com/yangecnu/p/Introduce-2-3-Search-Tree.html)

2-3树是多叉树，它同样是一个平衡查找树。

二叉树中，每个节点最多只储存一个数据项的同时，最多也只有左右两条链接。而2-3树则不同：

##### 定义

2-3树是一个多叉树。一个节点可以保存1个或2个数据项。可以有0-3个子节点。

1. 有一个数据项的节点必须有2个子节点。
2. 有二个数据项的节点必须有3个子节点。
3. 每个节点的数据项按照，数据项的key，从左到右保持从小到大的顺序。
4. 两个key之间的子树的key的值，大于父节点左key，小于父节点的右key.
5. 作为平衡树，所有从leaf到root的path的高度相同，因此所有的叶子节点都是位于同一层。
6. ⚠️2-3树的节点分裂是：自底向上的（不能预分裂），而且2-3树节点分裂必须用到新数据项。
7. 由1，2可知，除了叶节点不允许出现空节点。

#### 作业

We may need to update some keys stored in some internal nodes even if no leaf is split during the insertion. 错误的, 他不会插入到右边最小的, 修改internal, 他只会插入左边那个节点, 直到分裂为止. 

Suppose that no leaves are merged during the deletion. How many keys in the internal nodes need to be updated? Select all possible answers.  0 ,1,2 都有可能. 我选了 0 ,1  

比如把root删除, 可能要更新root和更新leaf. 

## lec3 均摊分析和splay

算法导论书中介绍了两种方法

Accounting Method 和 Potential Method

Accounting Method，要求你先计算出每个操作要“存”多少钱，然后给别的操作消费。

Stack的每次PUSH都花2元，1元是支付自身的操作，还有1元存起来。

接下来任意的POP和Multi-POP就不用花钱了，因为PUSH操作已经付过了。

这样上界就被我们进一步限制到了O(2n) = O(n)

### 势能

每次的PUSH，Stack的长度都加1，这就好像过山车在爬坡，积累1个势能单位，让其能够在后续的POP和Multi-POP回归到长度为0的状态**。**

无论Stack有多长，我们都有足够的势能单位，让Stack回归到0。

比如Stack的例子：

^c_i = c_i + P_i - P_i-1，摊还代价等于实际代价加上potential change，这里的势能表示stack中元素个数，代价表示时间，这个相加表示什么呢？这个就很难让人理解。其实它什么都不表示。所以它仅仅是一个获得某个操作摊还代价的方法而已。

pop, 代价1, 势能-1, 所以均摊为0

如果能定义一个势函数，使得对于任意的n, 势能都比初始的势能大 ，则总摊还代价 给出了总实际代价 的一个上界。

参考  https://zhuanlan.zhihu.com/p/87355970

##### 作业

作为potential function 

1. opposite number of available cells in the array 不行, 因为可能为负, 一开始是0 .就不满足对于任意的n, 势能都比初始的势能大
2. number of available cells in the array 不行, 

答案是 number of elements stored in the array minus number of available cells in the array 可以

### splay tree

参考https://algorithmtutor.com/Data-Structures/Tree/Splay-Trees/ 

splay tree的amortized cost (log n) 

n指的是进行操作时的树的size。因为log n对应的是u的rank的变化，而u的rank至多是log (size of T)。

优点

1. 好实现
2. no extra space
3. adaptive, 多次查询同一个很快

缺点:  最坏要O(n)

查询:  find key ,然后 splay 到root 

插入:  二叉树插入, 然后把这个节点再splay到root. 

删除: 找到key, 然后splay 到root . 

如果children >=2 , 删除key后splay 左边子树中最大的节点到A的root, 然后把右子树接到右边.

During a splay operation, there can be at most one single rotation. 对的, single rotation就是一种情况, 大部分时候都是zig zag 或者zag zig啥的. 

作业 During a splay operation, there can be as many as Θ(*n*) rotations in the worst case. 对的.

## lec4  堆

![image-20220330100728595](C:\Users\12638\AppData\Roaming\Typora\typora-user-images\image-20220330100728595.png)

Binary heap  就是 除了最后一层, 别的层都满了, 然后node要么小于 children 要么大于children . 

BuildHeap和Merge能够以 O(n) 执行。

为了降低Merge复杂度，人们不得不使用**指针**，这就诞生了左式堆。左堆本质上是一个二叉树.

### leftist heap

特点: merge O(logn) ,插入删除均摊时间是Ologn

【Theorem】A leftist tree with r nodes on the right path must have at least 2r – 1 nodes.

定义 : The null path length, Npl(X), X  最短路径from X to a node without two children.  Define Npl(NULL) = –1.

Note: 
Npl(X) = min { Npl(C) + 1 for all C as children of X }

【Definition】

The leftist heap property is that for every node X in the heap, 左孩子 Npl  >= 右孩子的 Npl

#### merge

step 1 先merge  h1的right 和 H2 

step2 attach 两棵树

step 3 可能要左右交换

插入就相当于merge一个节点, 也是O(lgn)

Deletemin要掌握.

不考删除, 删除要修复leftist 性质 .

```cpp
PriorityQueue Merge( PriorityQueue H1, PriorityQueue H2 )
{ 
  if (H1==NULL) return H2;
  if (H2==NULL) return H1;
  if (H1->Element > H2->Element)
    swap(H1, H2);  //swap H1 and H2
    if (h1->left == NULL)
        h1->left = h2;
    else
    {
        h1->right = Merge(h1->right, h2);
        if (h1->left->dist < h1->right->dist)
            swapChildren(h1);
        h1->dist = h1->right->dist + 1;
  }
  return H1;
}
```

The depth of a node is 到root的距离

### skewed heap

斜堆是左式堆的一个变体，各方面性能和左式堆相似。

目标: Any M consecutive operations take at most O(M log N) time.

merge 总是左右互换

Insertion 和deletemin 可以通过merge来实现

delete和decrease key 很多文献和书都不提, 可以认为不支持. 

skew heaps优点:  不用额外空间存储path length, 不需要考虑交换

### binomial heap

这么一来虽然Merge的性能被搞上去了，但是Insert的性能却下来了。毕竟，从平均的角度看，左式堆和斜堆Insert的平均复杂度是 O logn ，而二叉堆Insert的平均复杂度是 O 1 

因此有人发明了二项队列(binomial queue)，该数据结构Insert，DeleteMin和Merge的最坏复杂度为 O logn，而且Insert的平均复杂度是 O1 

性能和leftist 大O 是一样的, 

优点, 空的堆n次insertion, 平均每次O1. 用了一种完全不同的思路, 而且也是斐波那契heap的前置思路. 

通过递归的方式来定义

高度 = 0 , 叫做 B0 . single node

高度 = k , 叫做Bk,  有两个Bk-1 

Bk的高度是k, root有k个children  分别是 B 0, B1, B2 ..  Bk-1

6个node

110 , 1个B2 和1个B1, 0个B0

Findmin 是 O lgn, 维护最小值就可以变成O1

##### Insertion

合并树和二进制的加法是一一对应的.

  ```cpp
  Insert(H,x)
  create B0 with key x and add it to H
      i = 0
      while(H has two Bi){
          combine them into Bi+1;
          i++;
      }
  ```

##### deletemin 

```
1 find the bk that contains the min O(1)
2 h = h - Bk O(1)
3 H' = Bk - root    O(k) = lgn 
4 merge(H , H')   logn 
```

##### decrease key

两种方法证明n次插入需要 O(n)时间

 proof 1  combine 次数

n/.2  + n/4 + n/8    求和是On

proof 2 

potential function  = #trees in D 

actual cost = O1 + #combines = O1 + 1-  trees 变化

left child -next -sibling

### 作业

The right path of a skew heap can be arbitrarily long.  对的



## lec5

### Inverted File Index

用在搜索引擎. 每个文件检查string , io太慢了!

Compact Version - Inverted File Index

space O(f(V))

 ```
 while ( read a document D ) {
     while ( read a term T in D ) {
         if ( Find( Dictionary, T ) == false )
             Insert( Dictionary, T );
         Get T’s posting list;
         Insert a node to T’s posting list;
     }
 }
 Write the inverted index to disk;
 ```

word stemming , 找词根

stop words,  a the it不需要index them , 可以简单地删除他们. 

```
BlockCnt = 0; 
while ( read a document D ) {
  while ( read a term T in D ) {
    if ( out of memory ) {
      Write BlockIndex[BlockCnt] to disk;
      BlockCnt ++;
      FreeMemory;
    }
    if ( Find( Dictionary, T ) == false )
      Insert( Dictionary, T );
    Get T’s posting list;
    Insert a node to T’s posting list;
  }
}
```

动态索引

小的auxiliary index 作为新帖子, 查询就查main index和副index

每个一段时间合入auxiliary index

数据压缩

存储gap而不是大数字

不用都返回, 返回部分, 比如谷歌page rank. 

频率小的比较重要, 根据频率小的进行一次搜索, 然后频率放大些进行一次搜索, 如果结果差不多就说明稳定了, 就可以根据这个阈值. 

#### 精确和recall

搜索引擎两个指标

Precision P = RR / (RR + IR)  取到相关/ 所有取到

Recall      R = RR / (RR + RN)   取到相关/所有相关

可能recall 多 但是不精确, 可能精确但是recall少. 

Data retrieval vs. Information retrieval。

data retrieval指的是最基础的抓取包含关键词的文件的过程。比如你搜the apple company，这一过程会返回所有包含apple且包含company的files。要考虑响应时间和index space.  Information retrieval指的是搜索引擎理解了你想要的东西，然后抓取了包含这件东西的文件。比如你搜the apple company，这一过程会返回和apple Inc.相关的files。只有在information retrival的时候，我们才需要去测试relecancy。

## lec6 回溯

```cpp
dfs(u)
    if u is bad
        return 
     else if u havs no children ,
	return u 
    else:
    for each good child v of u ,
    	path = dfs(u)
            if path != None:
				return u -> path. 
```

回溯, 就是dfs + 剪枝pruning

难点就是问题, 你要**转换为一棵树**, 然后要方便**剪枝**. 

#### N 皇后问题

可以证明N >3 一定存在解.一些特殊的n(prime), 比如n=7 有快速解. 但是general n 是NP-hard.

没有用递归, 用循环, 为什么?

利用栈来实现递归. 

回退简单的时候可以用栈. 否则用递归.

时间复杂度上界:   每一步检查前面, On , 总共的选择是O (n!). 这是比较粗略的. 

#### Tumpike 问题

 解不唯一, 假定最小的a0 = 0, 

 maximum distance remaining in D  must result from either a n-i - ai or  ai- a0

D  ={ distance involving unknow points}

Input a multiset D 

Output a multiset A 

```python
TP(D,A) 
if D == 空集	
	return true
a = max( D) # Olgn
a' = max(A) -a # O n时间 .
# 可能是 a, 或者a' 产生这个距离. 
for x = a or a '
   # 计算 x到A 中每个点的距离. 
    delta = distance (x,a)  # O(n)
    if delta <= D{ # n次 find key
        remove delta from D
        add x to A.  # O1
        if TP(D,A):
            #如果可以把D 消掉, 
            return True
        else:
            # 回退. 
            remove x from A 
            add delta in D .
    }
return False # 这两条路失败了
```

最多N层递归.  

使用平衡BST即可. 

most distance.    O(n^2 lgn)  

rare distance. O(2^n lgn)

alhpa beta剪枝, 只用搜索  O(sqrt n)个节点即可. 

 换图， 

#### 作业

https://www.codeleading.com/article/76203270380/

Given the following game tree, which node is the first one to be pruned with α-β pruning algorithm?

选c, 剪去不用考虑的那个节点. 

#### proj2 

node 变大， edge 变大。
算法设计， 临接表： 临接表的图。

斐波那契堆没有优势， 优点就是decrease key ， 但是稀疏图decrease key 执行的次数不多。  多层函数嵌套， 操作过于复杂。 

binary heap为啥快？ 操作简单， 常系数小， 数组地址是连续的， 缓存命中率高。 

### lec7greedy


选尽可能多的活动：

1. shortest first。 
   但是可能造成多个冲突

2. lease overlap first 

3. smallest finish time first

 按完成时间排序
 如果和选择的活动不冲突， 那就加入。
 难点是证明 最后结果是最优的。
Proof1:
 Induction（showing the greedy solution 每一步都最优
 A： i1，i2 i3， 
 OPT:  
 Proof2:
 exchange argument： 
 证明所有可行解， 特别是最优解， 可以改成贪心解， 保证解的质量不会下降。 

 霍夫曼算法：

 ```python3
for each a :
   create a tree of single node 
 每次合并两棵频率最小的树， 树的频率等于叶子的频率之和。
 直到只有一棵树 结束。
 ```

课后思考题， 如果词已经按频率递增排序里， 那么线性时间可以找到最优树。 对吗？

每次都选频率最小的两个树，合并为t3. 

每轮的t3 频率是递增的。

解答 ： 可以用两个优先队列来做， 第一个队列存原始从小到大， 第二个队列存每次产生的t3。 　

找最小的两棵，就是在两个队列前两个里面找，找到后pop两个成为p3. p3 放到第二个队列最后可以保证是递增的， （为什么？） 生成的T3 一定是某两个的和=A+B，如果他比之前生成的的T = C+D小，那么一定有C>A或者D>B, 前面的T3就不可能是当时最小两个的和。因为当时就应该把A或者B选进来。 

#### proj4

哈夫曼树WPL最小， 





#### 作业

Let S be the set of activities in Activity Selection Problem. Then the earliest finish activity am must be included in all the maximum-size subset of mutually compatible activities of S. 这是错的. am只是贪心算法的解一定包含，但是有可能有其他最优解不包含.

### lec8 分而治之

Counting Inversions:

输入 A 数组求逆序对。 

逆序对应用： 作为你和你朋友偏好的差异。 

分为 left 逆序， right 逆序， split 逆序 一个左一个右。 

归并排序。 

```python
if n <=1 :
  return (A,0)
else:
  (C,leftInv) = sortandcount(left part of A) #T(n/2)
  (D,rightInv) = sortandcount(right part of A) #  T(n/2)
  (B,splitInv) = mergeandCount(C,D)  #O(n)
  return (B,leftinv+rightinv+splitinv)
```

可以达到nlogn

##### closest pair 问题

有一些点， 要找欧式距离最近的两个点。

把所有点分成三类， left pair， right pair， split pair。

按 x coord 和y coord 排序

```python
if n <=3 :
   trivial
Lx = pts on left half plane, sorted by x coord
Ly = pts on left half plane, sorted by y coord
Rx = pts on right half plane, sorted by x coord
Rx = pts on right half plane, sorted by y coord
（l1,l2） = closest pair(Lx,Ly)#T(n/2)
(r1,r2) = closest pair (Rx,Ry) #T(n/2)
delta =  min{ d(l1,l2),d(r1,r2)} # O(1)
(s1,s2) = closest pair(Px,Py,delta) # O(n) 只用考虑距离小于delta的就可以了。

return best of （l1,l2）,(r1,r2),(s1,s2)
```

a split pair (Px,Py) 

d(Px,Py) < delta  => | xi-xj| < delta

就是不断切分空间， 切分成四个正方形。

```python
closest pair(Px,Py,delta)

x‘ = largest x-coord of pts in left half phone
Sy = {q1,q2... ql} x  in [x'-delta,x'+delta ] sorted by y-coord
best = delta
Best pair = null
for i in [1,l-1]:
  for j in [1: min{l,l-i}]:
    if d(qi,qi+j) < best:
      best = d(qi,qi+j)
      bestpair = (qi,qi+j)
return bestpair
```

每层n， 那就总共nlgn 。 这里。fn = n，  a就是节点出度， b就是子问题的规模， r =1， 

fn = n^2,   如果出度是2， 越分越小， 就总共是 n^2。     

fn = sqrtn,  总共是 n



#### 主定理

https://zhuanlan.zhihu.com/p/100531135

考试要背一下1，2，4形式套公式。为了快速写题目， 然后3形式最重要。 

作业题

如果不是n^d形式的，比如nlogn，d应该怎么取？

https://cs.stackexchange.com/questions/96422/how-to-solve-tn-2t%E2%88%9Anlog-n-with-the-master-theorem

作业题2 

 solve a problem with input size *N* by divide and conquer algorithm, among the following methods, __ is the worst.

A.  divide into 2 sub-problems of equal complexity *N*/3 and conquer in *O*(*N*) 第一个是on， 第二行是2/3n， 那越来越小， 最后就是on。

B.divide into 2 sub-problems of equal complexity *N*/3 and conquer in *O*(NlogN) 第一个是logn， 第二个小， 所以最后nlogn

C.divide into 3 sub-problems of equal complexity *N*/2 and conquer in *O*(*N*)  

D.divide into 3 sub-problems of equal complexity *N*/3 and conquer in *O*(*Nl**o**g**N*)





## 期中考

被证明只具有伪多项式时间算法解的问题有[背包问题](https://zh.wikipedia.org/wiki/背包问题)，[子集合加总问题](https://zh.wikipedia.org/wiki/子集合加總問題)。

一个具有伪多项式时间复杂度的[NP完全问题](https://zh.wikipedia.org/wiki/NP完全)称之为[弱NP完全问题](https://zh.wikipedia.org/w/index.php?title=弱NP完全&action=edit&redlink=1)，而在[P!=NP](https://zh.wikipedia.org/wiki/P/NP问题)的情况下，若一个NP完全问题被证明没有伪多项式时间复杂度的解，则称之为[强NP完全问题](https://zh.wikipedia.org/w/index.php?title=强NP完全&action=edit&redlink=1)。

不考动态规划， 

#### 判断题

In a red-black tree, the number of internal nodes in the subtree rooted at *x* is no more than 2^bh(x)−1 where *bh*(*x*) is the black-height of *x*. 错的

Word stemming 是啥？ 就是去掉各种后缀获得词根。

For one operation, if its worst-case time bound is Θ(*l**o**g**N*), then its amortized time bound must be *O*(*l**o**g**N*).  这是对的

While accessing a term, hashing is faster than search trees. 对的

### lec9动态规划

例子1 ：

weighted indepdent set on paths:

怎么重构最优解？

```
if n == 0:
	return null
if n ==1 :
	return {v1}
else:
	if c[n] == c[n-1]:
		S = reconstruct(n-1)
		return S
	else:
		S = reconsturct(n-2)
		S += {vn}
		return S
```

第一步， 定义子问题。

第二步， 找到最优解的值之间的递归关系。

第三步， 计算最优值。

第四步，重构最优解。



weighted interval scheduling

之前用贪心解决过， 

To solve a problem by dynamic programming instead of recursions, the key approach is to store the results of computations for the subproblems so that we only have to compute each different subproblem once. Those solutions can be stored in an array or a hash table.



#### Let 10 动态规划2 

找到最短距离。

Dijkstra ，时间复杂度为  vlogv +e， 但是要求图没有负数边， 不然就不对了。 

这其实是一个动态规划



##### Bellman-Ford 算法

也是dp， 也要定义一个子问题。但是很难定义谁先谁后。

首先来看最优解的结构。 

子问题

解决方法就是，一步步增加步数，先计算每个点的 0步， 然后计算每个点的1步， 然后计算每个点的两步，直到每个点都稳定为止。

Lemma： G 没有负边。《=》  c【v】【n-1】 = c【v】【n】 for 所有顶点

此时也就是输出了最优解， 如果这条不成立的话就输出存在负边。

时间复杂度是多少？O（VE ）

空间复杂度： O（V平方）， C【v】【i-1】 可以丢弃， 空间减少到  O（V）。



##### All pair shorest path

输入：  有向图， 

输出： 每个pair都距离

如果没有负边，就直接 dijkstra。 O（v平方 logv + EV）

有负边：  bellman-ford 需要 O（E V平方）

可以用floyd warshall O（V三次方） 也是用DP

V 定义为1 到n

定一个rank， rank是路径上最大的index 。

子问题怎么定义的？

i 是起点， k表示rank的上限。 

找到各个部分最好的path。

空间复杂度： O n三次方， 优化后可以到On平方。



如果走了第一个点， 第三步不能走红点， 那么动态规划就不能用了。





时间复杂度是伪多项式



作业：

In dynamic programming, we derive a recurrence relation for the solution to one subproblem in terms of solutions to other subproblems. To turn this relation into a bottomup dynamic programming algorithm, we need an order to fill in the solution cells in a table, such that all needed subproblems are solved before solving a subproblem. For each of the following relations, give such a valid traversal order, or if no traversal order is possible for the given relation, briefly justify why. 

i. A(i, j) = F(A(i, j − 1), A(i − 1, j − 1), A(i − 1, j + 1))

 ii. A(i, j) = F(A(min{i, j} − 1, min{i, j} − 1), A(max{i, j} − 1, max{i, j} − 1)) 

iii. A(i, j) = F(A(i − 2, j − 2), A(i + 2, j + 2))

i. Solve A(i, j) for(i from 0 to n: for(j from 0 to n)) 

ii. Solve A(k, k) for(k from 0 to n) then solve rest in any order 

iii. Impossible: cyclic.
