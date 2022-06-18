For a skew heap with *N* nodes, the worst-case running time of all operations (insert/delete min/merge) is *O*(*N*).

T

F

------

1-2

分数 2

作者 叶德仕

单位 浙江大学

In the bin packing problem, we are asked to pack a list of items *L* to the minimum number of bins of capacity 1. For the instance *L*, let *FF*(*L*) denote the number of bins used by the algorithm **First Fit**. The instance *L*′ is derived from *L* by deleting one item from *L*. Then *FF*(*L*′) is at most of *FF*(*L*).

T

F

------

1-3

分数 2

作者 叶德仕

单位 浙江大学

Consider a state-flipping algorithm for the Maximum-Cut problem. We say that partitions (*A*,*B*) and (*A*′,*B*′) are neighbors under the *k*-flip rule if (*A*′,*B*′) can be obtained from (*A*,*B*) by moving at most *k* nodes from one side of the partition to the other. If (*A*,*B*) is a local optimum under the *p*-flip rule, it is also a local optimum under the *k*-flip rule for every *k*<*p*.

T

F

------

1-4

分数 2

作者 杨洋

单位 浙江大学

In a search engine, thresholding for query retrieves the top *k* documents according to their weights.

T

F

------

1-5

分数 2

作者 徐镜春

单位 浙江大学

The Huffman code is one kind of optimal prefix codes. For a given alphabet and its characters' frequencies，the Huffman codes may not be unique, but the Huffman code **length** of each character is unique.

T

F

------

1-6

分数 2

作者 徐镜春

单位 浙江大学

A randomized Quicksort algorithm has an *O*(*N*log*N*) expected running time, only if all the input permutations are equally likely.

T

F

------

1-7

分数 2

作者 何钦铭

单位 浙江大学

A 2-3 tree with 12 leaves may have at most 10 nonleaf nodes.

T

F

------

1-8

分数 2

作者 冼伟钊

单位 浙江大学

The 4-queen problem has exactly 2 distinct solutions.

T

F

------

1-9

分数 2

作者 沈鑫

单位 浙江大学

Givien two *n*×*n* matrices *A* and *B*, the time complexity of the simple matrix multiplication *C*=*A*⋅*B* is *O*(*n*3). Now let's consider the following Divide and Conquer idea:

Divide each matrix into four 2*n*×2*n* submatrics as follows:

[*C*1*C*3*C*2*C*4] = [*A*1*A*3*A*2*A*4]⋅[*B*1*B*3*B*2*B*4]

We recursively calculate each block of *C* as *C*1=*A*1⋅*B*1+*A*2⋅*B*3 and so on. This can reduce the time complexity of the simple calculation.

T

F

------

1-10

分数 2

作者 沈鑫

单位 浙江大学

Recall the discussion about the Maximum Finding Problem (that is, to find the maximum among *n* numbers in an array), Common CRCW memory strategy is used to assure *T*(*n*)=*O*(1) for the parallel algorithm. Actually, we can also apply Arbitrary CRCW memory strategy to keep *O*(1) time complexity. Now let us consider a new memory strategy, namely the **C**oncurrent **R**ead **O**wner **W**rite (CROW). It means that each memory has an official "owner". Only the "owner" can write to the corresponding memory. Then there is no parallel algorithm that can solve the problem with *T*(*n*)=*O*(1) using CROW memory strategy.

T

F

------

1-11

分数 2

作者 叶德仕

单位 浙江大学

If *L*1≤*p**L*2 and *L*2∈*NP*, then *L*1∈*NP*.

T

F

------

1-12

分数 2

作者 叶德仕

单位 浙江大学

If a data structure supports an operation QI such that a sequence of *n* QI’s takes Θ(*n*2log*n*) time to perform in the worst case, then the amortized cost of a QI operation is Θ(*n*log*n*) , while the actual time of a single QI operation could be as high as Θ(*n*2log*n*).

T

F

------

1-13

分数 2

作者 冼伟钊

单位 浙江大学

Given 1000 runs and 8 tapes. If simple *k*-way merge is used, the minimum number of passes required is 5 (runs generation pass is not counted).

When measure the performance of parallel algorithm, we often use work load (*W*(*n*)) and worst-case running time (*T*(*n*)). How many evaluation metrics are asymptotically equivalent to *W*(*n*) and *T*(*n*)?

- *P*(*n*)=*W*(*n*)/*T*(*n*) processors and *T*(*n*) time (on a PRAM)
- *W*(*n*)/*p* time using any number of *p*≥*W*(*n*)/*T*(*n*) processors (on a PRAM)
- *W*(*n*)/*p*+*T*(*n*) time using any number of *p* processors (on a PRAM)

A.

0

B.

1

C.

2

D.

3

------

2-2

分数 3

作者 陈越

单位 浙江大学

Which of the following binomial trees can represent a binomial queue of size 141?

A.

*B*0 *B*2 *B*3 *B*7

B.

*B*0 *B*2 *B*3 *B*6 *B*6

C.

*B*0 *B*8

D.

*B*0 *B*1 *B*4 *B*5 *B*7

------

2-3

分数 3

作者 陈越

单位 浙江大学

Delete the minimum number from the given leftist heap. Which one of the following statements is TRUE?

![F3.JPG](https://images.ptausercontent.com/fb5912d6-552e-4c46-b2b0-4d4b35052bc5.JPG)

A.

3 is NOT the root

B.

24 is the left child of 12

C.

8 is the left child of 7

D.

12 is the right child of 6

------

2-4

分数 3

作者 陈越

单位 浙江大学

Merge the two given skew heaps. Which one of the following statements is FALSE?

![F1.JPG](https://images.ptausercontent.com/98a094d5-244d-4f88-b062-38123a9bb84d.JPG)

A.

1 is the root

B.

7 is the right child of 6

C.

9 is the right child of 5

D.

5 is the left child of 4

------

2-5

分数 3

作者 何钦铭

单位 浙江大学

After splaying at node 2 in the given tree, which of the following statements about the resulting tree is FALSE?

![123456（1）.jpg](https://images.ptausercontent.com/ec963ff9-f4f1-440f-927d-f24afaee9689.jpg)

A.

the depth of the tree is 4 (where the depth of the root is 1)

B.

node 5 is a child of node 2

C.

the degree of node 5 is 2

D.

node 3 is a leaf node

------

2-6

分数 3

作者 何钦铭

单位 浙江大学

After inserting 1 into the red-black tree given in the figure, which node(s) will have its/their color(s) changed?

![rbTree1.jpg](https://images.ptausercontent.com/917a1839-9671-453c-b829-db95328e858c.jpg)

A.

only 2

B.

both 2 and 4

C.

2, 3, and 4

D.

both 3 and 6

------

2-7

分数 3

作者 何钦铭

单位 浙江大学

After inserting 7 into the 2-3 tree given in the figure, how many of the following statements are TRUE?

(S1) The root still contains 9 only;

(S2) the tree grows higher;

(S3) 4 and 9 are in the same nonleaf node;

(S4) the interior node containing 12 keeps unchanged.

![2-3tree.jpg](https://images.ptausercontent.com/4a329767-858f-4c23-9446-4a3f7ae8b814.jpg)

A.

0

B.

1

C.

2

D.

3

------

2-8

分数 3

作者 何钦铭

单位 浙江大学

Insert 28, 23, 54, 61, 98, 37 into an initially empty AVL tree first. Then immediately insert one of the following keys. Which one will cause an RL rotation?

A.

10

B.

30

C.

60

D.

70

------

2-9

分数 3

作者 徐镜春

单位 浙江大学

Given a set of activities *S*={*a*1,*a*2,⋯,*a**n*}. Each *a**i* takes place during a time interval [*s**i*,*f**i*).
If an instance *S* given as the following, the maximum-size of mutually compatible activities is __.

![greedy试题.png](https://images.ptausercontent.com/a43197c1-cb65-4b21-8792-1e6bc287e587.png)

A.

4

B.

5

C.

6

D.

7

------

2-10

分数 3

作者 叶德仕

单位 浙江大学

In the bin packing problem, suppose that the maximum size of the items is bounded from above by *α*<1. Now let's apply the Next Fit algorithm to pack a set of items *L* into bins with capacity 1. Let *NF*(*L*) and *OPT*(*L*) denote the numbers of bins used by algorithms Next Fit and the optimal solution. Then for all *L*, we have *NF*(*L*)<*ρ*⋅*OPT*(*L*)+1 for some *ρ*. Which one of the following statements is FALSE?

A.

*ρ*=1−*α*1, if 0≤*α*≤1/2.

B.

*ρ*=2, if *α*>1/2.

C.

If *L* = (0.5, 0.3, 0.4, 0.8, 0.2, 0.3), then *NF*(*L*)=4.

D.

*ρ*=2*α* if 0≤*α*≤1

------

2-11

分数 3

作者 叶德仕

单位 浙江大学

There are *n* jobs, and each job *j* has a processing time *t**j*. We will use a local search algorithm to partition the jobs into two groups A and B, where set A is assigned to machine *M*1 and set B to *M*2. The time needed to process all of the jobs on the two machines is *T*1=∑*j*∈*A**t**j*, *T*2=∑*j*∈*B**t**j*. The problem is to minimize ∣*T*1−*T*2∣.

Local search: Start by assigning jobs 1,…,*n*/2 to *M*1, and the rest to *M*2.
The local moves are to move a single job from one machine to the other, and we only move a job if the move decreases the absolute difference in the processing times. Which of the following statement is true?

A.

The problem is NP-hard and the local search algorithm will not terminate.

B.

When there are many candidate jobs that can be moved to reduce the absolute difference, if we always move the job *j* with maximum *t**j*, then the local search terminates in at most *n* moves.

C.

The local search algorithm always returns an optimal solution.

D.

The local search algorithm always returns a local solution with 21*T*1≤*T*2≤2*T*1.

------

2-12

分数 3

作者 杨洋

单位 浙江大学

Two spam mail detection systems are tested on a dataset with 7981 ordinary mails and 2019 spam mails. System A detects 200 ordinary mails and 1800 spam mails, and system B detects 160 ordinary mails and 1500 spam mails. If our primary concern is to keep the important mails safe, which of the following is correct?

A.

Precision is our primary concern and system A is better.

B.

Recall is our primary concern and system B is better.

C.

Precision is our primary concern and system B is better.

D.

Recall is our primary concern and system A is better.

------

2-13

分数 3

作者 徐镜春

单位 浙江大学

The Online Hiring Algorithm ( hire only once ) is described as the following:

```
int OnlineHiring ( EventType C[ ], int N, int k )
{
    int Best = N;
    int BestQ = -INFINITY ;
    for ( i=1; i<=k; i++ ) {
        Qi = interview( i );
        if ( Qi > BestQ )   BestQ = Qi;
    }
    for ( i=k+1; i<=N; i++ ) {
        Qi = interview( i );
        if ( Qi > BestQ ) {
            Best = i;
            break;
        }
    }
    return Best;
}
```

Assume that the quality input C[ ] is uniformly random.
When *N* = 271 and *k* = 90, the probability of hiring the *N*th candidate is__.

A.

1/*e*

B.

1/*N*

C.

1/3

D.

1/*k*

------

2-14

分数 3

作者 冼伟钊

单位 浙江大学

Given the following game tree, the red node will be pruned with α-β pruning algorithm if and only if __.

![bt.jpg](https://images.ptausercontent.com/3720a474-284a-4468-97d0-c317a92d1eef.jpg)

A.

6≤*x*≤13

B.

*x*≥13

C.

6≤*x*≤9

D.

*x*≥9

------

2-15

分数 3

作者 冼伟钊

单位 浙江大学

Suppose that the replacement selection is applied to generate longer runs with a priority queue of size 5. Given the sequence of numbers { 17, 2, 6, 57, 51, 86, 5, 94, 43, 54, 39, 87, 29}, the longest run contains ____ numbers.

A.

5

B.

6

C.

7

D.

8

------

2-16

分数 3

作者 沈鑫

单位 浙江大学

Givien two *n*×*n* matrices *A* and *B*. Let's consider the following Divide and Conquer idea to do matrix multiplication *C*=*A*⋅*B*.

Divide each matrix into four 2*n*×2*n* submatrics as follows:

[*C*1*C*3*C*2*C*4] = [*A*1*A*3*A*2*A*4]⋅[*B*1*B*3*B*2*B*4]

We define *P*1,*P*2,⋯,*P*7 as follows:

*P*1=*A*1⋅(*B*2−*B*4)

*P*2=(*A*1+*A*2)⋅*B*4

*P*3=(*A*3+*A*4)⋅*B*1

*P*4=*A*4⋅(*B*3−*B*1)

*P*5=(*A*1+*A*4)⋅(*B*1+*B*4)

*P*6=(*A*2−*A*4)⋅(*B*3+*B*4)

*P*7=(*A*1−*A*3)⋅(*B*1+*B*2)

Here all the matrix multiplications are done **recursively**. Then each part of *C* can be calculated by simple additions and subtractions among *P*1,*P*2,⋯,*P*7.

Which of the following is the closest to the actual time complexity?

A.

*O*(*n*2log2*n*)

B.

*O*(*n**e*)

C.

*O*(*n*log27)

D.

*O*(*n*3)

------

2-17

分数 3

作者 沈鑫

单位 浙江大学

How many of the following sorting methods use(s) Divide and Conquer algorithm?

- Heap Sort
- Insertion Sort
- Merge Sort
- Quick Sort
- Selection Sort
- Shell Sort

A.

2

B.

3

C.

4

D.

5

------

2-18

分数 3

作者 叶德仕

单位 浙江大学

Which one of the following statements is FALSE?

A.

For red-black trees, the total cost of rebalancing for *m* consecutive insertions in a tree of *n* nodes is *O*(*n*+*m*).

B.

To obtain *O*(1) armortized time for the function **decrease-key**, the potential function used for Fibonacci heaps is Φ(*H*)=*t*(*H*)+*m*(*H*), where *t*(*H*) is the number of trees in the root list of heap *H*, and *m*(*H*) is the number of marked nodes in *H*.

C.

Let *S*(*x*) be the number of descendants of *x* (*x* included). If the potential function used for splay tree is Φ(*T*)=∑*x*∈*T*log*S*(*x*) , then the amortized cost of one splay operation is *O*(log*n*).

D.

In the potential method, the amortized cost of an operation is equal to the actual cost plus the increase in potential due to this operation.

------

2-19

分数 3

作者 叶德仕

单位 浙江大学

Which one of the following statements is FALSE?

A.

SAT, Vertex Cover, Hamiltonian Cycle, Clique, Knapsack, Bin Packing, and Domination Set problems are all NP-completeness problems.

B.

If there is a polynomial time (1+2*n*1)-approximation algorithm for Vertex Cover with *n* being the total number of vertices in the graph, then P=NP.

C.

If there is a polynomial time 3/2-approximation algorithm for K-Center, then P=NP.

D.

Given a weighted directed acyclic graph (DAG) *G* and a source vertex *s* in *G*, it is NP-hard to find the longest distances from *s* to all other vertices in *G*.

------

2-20

分数 3

作者 叶德仕

单位 浙江大学

Which one of the following statements is FALSE?

A.

A language *L*1 is polynomial time transformable to *L*2 if there exists a polynomial time function *f* such that *w*∈*L*1 if *f*(*w*)∈*L*2.

B.

*L*1≤*p**L*2 and *L*2≤*p**L*3 then *L*1≤*p**L*3.

C.

If *L*1∈*P* then *L*1⊆*NP*∩ co-*NP*.

D.

If language *L*1 has a polynomial reduction to language *L*2, then the complement of *L*1 has a polynomial reduction to the complement of *L*2.

The function `DeleteRt` is to delete the root of a subtree with index `Pos` from a binomial queue `H`. The rest of the subtree is then stored as a new binomial queue and returned.

#### 填空题

```c++
BinQ DeleteRt( BinQ H, int Pos )
{
    BinTree OldRoot, SubTree;
    BinQ NewBinQ;
    int p;
    
    OldRoot = H->TheTrees[Pos];
    SubTree = OldRoot->LeftChild;
    free(OldRoot);
    NewBinQ = Initialize();
    NewBinQ->CurrentSize = 3 分;
    for ( 3 分 ) {
        NewBinQ->TheTrees[p] = SubTree;
        SubTree = SubTree->NextSibling;
        NewBinQ->TheTrees[p]->NextSibling = NULL;
    }
    return NewBinQ;
}
```

#### 编程

CYLL has an integer-typed variable *X* whose initial value is 1. The variable can be updated in each step by applying either of the two operations:

1. Multiply the variable by a fixed integer *K*: *X*=*X*×*K*
2. Add an integer *T* (1≤*T*≤10) to the number: *X*=*X*+*T*

Given two integers *N* and *K* as inputs, can you help CYLL to decide the minimum number of steps required before she obtains the number *N* as the variable value?

### Format of functions：

```c++
int FindMinSteps(int N, int K);
```

Here *N* (1≤*N*≤106) is the target number and *K* (1≤*K*≤*N*) is the multiplication factor, which are integers as described in the problem specification.

The function is expected to return the minimum number of steps before the variable *X* reaches value *N*. (See the sample input/output for a concrete example.)

### Sample program of judge：

```c++
#include <stdio.h>

int FindMinSteps(int N, int K);

int main()
{
  int N, K;
    
    scanf("%d%d", &N, &K);
    
    printf("%d", FindMinSteps(N, K));
    
    return 0;
}    

/* Implement the 'FindMinSteps' function here */
```

### Sample input：

```in
101 2
```

### Sample output：

```out
6
```

### Sample explanation :

step 1: *X*=1+10=11

step 2: *X*=11∗2=22

step 3: *X*=22∗2=44

step 4: *X*=44+6=50

step 5: *X*=50∗2=100

step 6: *X*=100+1=101

**Note** that this is not the only way to reach 101 in 6 steps, however, we care about the minumum number of steps, which is unique, rather than how you reach there.

代码长度限制

16 KB

时间限制

200 ms

内存限制

64 MB
