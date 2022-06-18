1-1

分数 2

作者 徐镜春

单位 浙江大学

In order to solve the maximum finding problem by a parallel algorithm with *T*(*n*)=*O*(1) , we need work load *W*(*n*)=Ω(*n*2) in return.

T

F

------

1-2

分数 2

作者 徐镜春

单位 浙江大学

For the recurrence equation *T*(*N*)=9*T*(*N*/3)+*N*2*l**o**g**N*，we obtain *T*(*N*)=*O*(*N*2*l**o**g**N*) acorrding to the Master Theorem.

T

F

------

1-3

分数 2

作者 叶德仕

单位 浙江大学

To solve the vertex cover problem, there is a greedy algorithm that collects the vertex with the highest degree (i.e., the one covering the largest number of edges) and remove it from the graph at each stage. This greedy algorithm achieves an approximation ratio of 2.

T

F

------

1-4

分数 2

作者 叶德仕

单位 浙江大学

Let *a*=(*a*1,*a*2,…,*a**i*,…,*a**j*,…,*a**n*) denote the list of elements we want to sort. In the quicksort algorithm, if the pivot is selected uniformly at random. Then any two elements get compared at most once and the probability of *a**i* and *a**j* being compared is 2/(*j*−*i*+1) for *j*>*i*, given that *a**i* or *a**j* is selected as the pivot.

T

F

------

1-5

分数 2

作者 叶德仕

单位 浙江大学

In local search, if the optimization function has a constant value in a neighborhood, there will be a problem.

T

F

------

1-6

分数 2

作者 何钦铭

单位 浙江大学

In a Turnpike Reconstruction Problem, given distance set D = { 2, 2, 4, 6, 6, 8 }, x1~x4 = ( 0, 2, 6, 8 ) is the only solution provided that x1 = 0.

T

F

------

1-7

分数 2

作者 何钦铭

单位 浙江大学

In general, for a 3-way merge we need 6 input buffers and 2 output buffers for decreasing the number of passes.

T

F

------

1-8

分数 2

作者 陈越

单位 浙江大学

Amortized bounds are weaker than the corresponding worst-case bounds, because there is no guarantee for any single operation.

T

F

------

1-9

分数 2

作者 卜佳俊

单位 浙江大学

If a leftist heap can be implemented recursively, so can its counterpart skew heap.

T

F

------

1-10

分数 2

作者 杨洋

单位 浙江大学

For the document-partitioned strategy in distributed indexing, each node contains a subset of all documents that have a specific range of index.

T

F

------

1-11

分数 2

作者 杨洋

单位 浙江大学

The following binary search tree is a valid red-black tree.

![br-tree.png](https://images.ptausercontent.com/8b3f6083-11d6-490f-b7fc-5b180064c3ae.png)

T

F

------

1-12

分数 2

作者 Can Wang

单位 浙江大学

An (1+*ϵ*)-approximation scheme of time complexity (*n*+1/*ϵ*)3 is a PTAS but not an FPTAS.

T

F

------

1-13

分数 2

作者 Can Wang

单位 浙江大学

If P = NP then the Shortest-Path (finding the shortest path between a pair of given vertices in a given graph) problem is NP-complete.

To solve a problem with input size *N* by divide and conquer, algorithm A divides the problem into 6 subproblems with size *N*/2 and the time recurrences is

*T*(*N*)=6*T*(*N*/2)+Θ(*N*2).

Now we attempt to design another algorithm B dividing the problem into *a* subproblems with size *N*/4 and the time recurrences is

*T*(*N*)=*a**T*(*N*/4)+Θ(*N*2).

In order to beat algorithm A, what is the largest integer value of *a* for which algorithm B would be asymptotically faster than algorithm A?

A.

12

B.

18

C.

24

D.

36

------

2-2

分数 3

作者 徐镜春

单位 浙江大学

To solve a problem with input size *N* by divide and conquer, an algorithm divides the problem into 2 subproblems with size *N* (assuming it is an integer ) and the time recurrences is

*T*(*N*)=2*T*(*N*)+log(*N*).

What is the overall time complexity of this algorithm?

A.

*O*(log(*N*))

B.

*O*((log(*N*))2)

C.

*O*(log(*N*)loglog(*N*))

D.

*O*(*N*log(*N*))

------

2-3

分数 3

作者 徐镜春

单位 浙江大学

Sorting-by-merging is a classic serial algorithm. It can be translated directly into a reasonably efficient parallel algorithm. A recursive description follows.

MERGE−SORT( A(1), A(2), ..., A(n); B(1), B(2), ..., B(n) )

Assume that *n*=2*l* for some integer *l*≥0

if n = 1 then return B(1) := A(1)

else call, in parallel, MERGE−SORT( A(1), ..., A(n/2); C(1), ..., C(n/2) ) and

- MERGE−SORT(A(n/2+1), ..., A(n); C(n/2+1), ..., C(n) )
- Merge (C(1),...C(n/2)) and (C(n/2 + 1),...,C(n)) into (B(1), B(2), ..., B(n)) with time O(n)

Then the MERGE−SORT runs in __ .

A.

*O*(*n*log*n*) work and *O*(log2*n*) time

B.

*O*(*n*log*n*) work and *O*(log*n*) time

C.

*O*(*n*log2*n*) work and *O*(log2*n*) time

D.

*O*(*n*log2*n*) work and *O*(log*n*) time

------

2-4

分数 3

作者 叶德仕

单位 浙江大学

In Activity Selection Problem, we are given a set of activities *S*={*a*1,*a*2,…,*a**n*} that wish to use a resource (e.g. a room). Each *a**i* takes place during a time interval [*s**i*,*f**i*).

Let us consider the following problem: given the set of activities *S*, we must schedule them all using the minimum
number of rooms.

**Greedy1**:
Use the optimal algorithm for the Activity Selection Problem to find the max number of activities that can be scheduled in one room. Delete and repeat on the rest, until no activities left.

**Greedy2**:

- Sort activities by start time. Open room 1 for *a*1.
- for *i*=2 to *n*
  if *a**i*​ can fit in any open room, schedule it in that room;
  otherwise open a new room for *a**i*​.

Which of the following statement is correct?

A.

None of the above two greedy algorithms are optimal.

B.

Greedy1 is an optimal algorithm and Greedy2 is not.

C.

Greedy2 is an optimal algorithm and Greedy1 is not.

D.

Both of the above two greedy algorithms are optimal.

------

2-5

分数 3

作者 叶德仕

单位 浙江大学

** Load balancing problem: **
We have *n* jobs *j*=1,2,…,*n* each with processing time *p**j*​ being an integer number.
Our task is to find a schedule assigning *n* jobs to 10 identical machines so as to minimize the makespan (the maximum completion time over all the machines).

We adopt the following local search to solve the above load balancing problem.

**LocalSearch: **

Start with an arbitrary schedule.

Repeat the following until no job can be re-assigned:

- Let *l* be a job that finishes last.
- If there exists a machine *i* such that assigning job *l* to *i* allows *l* finish earlier, then re-assign *l* to be the last job on machine *i*.
- If such a machine is not unique, always select the one with the minimum completion time.

We claim the following four statements:

1. The algorithm LocalSearch finishes within polynomial time.
2. The Load-balancing problem is NP-hard.
3. Let OPT be the makespan of an optimal algorithm. Then the algorithm LocalSearch finds a schedule with the makespan at most of 1.8 OPT.
4. This algorithm finishes within *O*(*n*2).

How many statments are correct ?

A.

0

B.

1

C.

2

D.

3

E.

4

------

2-6

分数 3

作者 何钦铭

单位 浙江大学

Given the following game tree, if node **b** is pruned with α-β pruning algorithm, which of the following statements about the value of node **a** is correct?

![a-b剪枝-1.jpg](https://images.ptausercontent.com/18b4e8b4-48d4-49fa-80b7-301cef357045.jpg)

A.

greater than 65

B.

less than 65

C.

greater than 68

D.

less than 68

------

2-7

分数 3

作者 何钦铭

单位 浙江大学

A replacement selection is applied to generate the max run with a priority queue of 5 records. When the sequence of numbers is { 11, 81, 17, 14, 94, 28, 35, X, …. } and the length of the first run is 7, what is the sufficient condition of X?

A.

less than 17

B.

greater than 17

C.

less than 35

D.

less than 94

------

2-8

分数 3

作者 何钦铭

单位 浙江大学

After inserting number 20 into a binomial queue of 6 numbers { 12, 13, 14, 23, 24, 35 }, which of the followings is impossible?

A.

the LeftChild link of the node 20 is NULL

B.

the NextSibling link of the node 20 is NULL

C.

the NextSibling link of node 14 may point to node 20

D.

the LeftChild link of node 12 may point to node 14

------

2-9

分数 3

作者 何钦铭

单位 浙江大学

The potential function *Q* of a binomial queue is the number of the trees. After merging two binomial queues *H*1 with 22 nodes and *H*2 with 13 nodes，what is the potential change *Q*(*H*1+*H*2)−(*Q*(*H*1)+*Q*(*H*2)) ?

A.

2

B.

0

C.

-2

D.

-3

------

2-10

分数 3

作者 陈越

单位 浙江大学

Start from *N* single-node splay trees, let's merge them into one splay tree in the following way: each time we select two splay trees, delete nodes one by one from the smaller tree and insert them into the larger tree. Then which of the following statements is NOT true?

A.

In any sequence of *N*−1 merges, there are at most *O*(*N*log*N*) inserts.

B.

Any node can be inserted at most log*N* times.

C.

The amortized time bound for each insertion is *O*(log2*N*).

D.

The amortized time bound for each merge is *O*(log*N*).

------

2-11

分数 3

作者 卜佳俊

单位 浙江大学

For the result of accessing the keys 1 and 2 in order in the splay tree in the following figure, let's define **size**(*v*)=number of nodes in subtree of *v* ( *v* included ) and potential *ϕ*=∑*v*⌊log2**size**(*v*)⌋, where ⌊*x*⌋ means the greatest interger no larger than *x*.

How many of the following statements is/are TRUE?

- the potential change from the **initial** tree to the **resulted** tree is -4
- 1 is the sibling of 4
- 5 is the child of 6

![图.png](https://images.ptausercontent.com/071d7a8c-c028-4160-a47c-398cf901bc96.png)

A.

0

B.

1

C.

2

D.

3

------

2-12

分数 3

作者 卜佳俊

单位 浙江大学

Merge the two skew heaps in the following figure. How many of the following statements is/are FALSE?

- the null path length of 8 is the same as that of 12
- 40 is the left child of 18
- the depths of 18 and 33 are the same

![heap.png](https://images.ptausercontent.com/9e9d9199-802c-4ae0-85a3-5d01d3500eff.png)

A.

0

B.

1

C.

2

D.

3

------

2-13

分数 3

作者 卜佳俊

单位 浙江大学

Insert { 9, 8, 7, 2, 3, 5, 6, 4 } one by one into an initially empty AVL tree. How many of the following statements is/are FALSE?

- the total number of rotations made is 5 (Note: double rotation counts 2 and single rotation counts 1)
- the expectation (round to 0.01) of access time is 2.75
- there are 2 nodes with a balance factor of -1

A.

0

B.

1

C.

2

D.

3

------

2-14

分数 3

作者 卜佳俊

单位 浙江大学

To build a leftist heap, we can start from placing all the keys as single-node heaps on a queue, and perform the following until only one heap is on the queue: dequeue two heaps, merge them, and enqueue the result.

Then the best description of the time complexity of this procedure is:

A.

*O*(*N*)

B.

*O*(log*N*)

C.

*O*(*N*log*N*)

D.

*O*(*N*)

------

2-15

分数 3

作者 杨洋

单位 浙江大学

Assume that there are 10000 documents in the database, and the statistical data for one query are shown in the following table. One metric for evaluating the relevancy of the query is F-α score, which is defined as ((1+ α)∙(precision*recall))/(α∙precision+recall). Then the F-0.5 (α=0.5) score for this query is:

|                    | **Relevant** | **Irrelevant** |
| ------------------ | ------------ | -------------- |
| **Retrieved**      | 4800         | 1200           |
| **Not Retrieved ** | 3200         | 800            |

A.

0.80

B.

0.72

C.

0.60

D.

0.65

------

2-16

分数 3

作者 杨洋

单位 浙江大学

After inserting { 3, 4, 5, 6, 1, 2, 7 } into an initially empty red-black tree, which of following is **False**?

A.

The resulting tree is a full tree.

B.

4 is the root with the black height as 2.

C.

3 is the right child of 2, and the color of 3 is red.

D.

5 is the left child of 6, and the color of 5 is black.

------

2-17

分数 3

作者 叶德仕

单位 浙江大学

Assume P≠NP, please identify the false statement.

A.

There cannot exist a ρ-approximation algorithm for bin packing problem for any *ρ*<3/2.

B.

In the minimum-degree spanning problem, we are given a graph G=(V, E) and wish to find a spanning tree T of G so as to minimize the maximum degree of nodes in T. Then it is NP-complete to decide whether or not a given graph has minimum-degree spanning tree of maximum degree two.

C.

In the minimum-degree spanning problem, we are given a graph G=(V, E) and wish to find a spanning tree T of G so as to minimize the maximum degree of nodes in T. Then there exists an algorithm with approximation ratio less than 3/2.

D.

In the knapsack problem, for any given real number *ϵ*>0, there exists an algorithm with approximation ratio less than 1+*ϵ*.

------

2-18

分数 3

作者 Can Wang

单位 浙江大学

If P and NP are different, which of the following statements is true?

A.

There is no polynomial time algorithm to solve the vertex cover problem.

B.

P ∩ NP-Complete ≠ ∅.

C.

We can find polynomial time solution for Hamilton cycle problem.

D.

P = NP-Complete.

------

2-19

分数 3

作者 Can Wang

单位 浙江大学

```
If X is a problem in class NP, then how many of the following statements is/are TRUE?
```

- There is no polynomial time algorithm for X.
- There is a polynomial time algorithm for X.
- If X can be solved deterministically in polynomial time, then P = NP.

A.

0

B.

1

C.

2

D.

3

------

2-20

分数 3

作者 叶德仕

单位 浙江大学

In the maximum satisfiability problem (MAX SAT), the input consists of *n* Boolean variables *x*1,…,*x**n*, *m* clauses *C*1,…,*C**m*(each of which consists of a disjunction(that is an “or”) of some number of the variables and their negations, e.g. *x*3∨*x*ˉ5∨*x*11, where *x*ˉ*i* is the negation of *x**i*), and a nonnegative weight *w**j* for each clause *C**j*. The objective of the problem is to find an assignment of the true/false to the *x**i* that maximizes the weight of the satisfied clauses.

A variable or a negated variable is a literal. The number of literals in a clause is called its length. Denote *l**j* to be the length of a clause *C**j* . Clauses of length 1 are called unit clauses.

**Randomized algorithm RA**: Setting each *x**i* to true with probability *p* independently.

Which of the following statement is false?

A.

Let *p*=1/2, the randomized algorithm RA is a 2-approximation algorithm.

B.

If *l**j*≥3 for each clause *C**j*. Let *p*=1/2, the randomized algorithm RA is a 9/8-approximation algorithm.

C.

If MAX SAT instances do not have unit clauses *x*ˉ*i*, we can obtain a randomized 5−12≈1.618-approximation algorithm for MAX SAT.

D.

One could obtain a better bound on optimal solution than ∑*j*=1*m**w**j* for MAX SAT.

The function `FindKey` is to check if a given `key` is in a B+ Tree with its root pointed by `root`.

Return `true` if `key` is in the tree, or `false` if not. The B+ tree structure is defined as following:

```
static int order = DEFAULT_ORDER;
typedef struct BpTreeNode BpTreeNode;
struct BpTreeNode {
    BpTreeNode** childrens;  /* Pointers to childrens. This field is not used by leaf nodes. */
    ElementType* keys;
    BpTreeNode* parent;
    bool isLeaf;  /* 1 if this node is a leaf, or 0 if not */
    int numKeys;  /* This field is used to keep track of the number of valid keys. 
    In an internal node, the number of valid pointers is always numKeys + 1. */
};


bool FindKey(BpTreeNode * const root, ElementType key){
    if (root == NULL) {
            return false;
    }
    int i = 0;
    BpTreeNode * node = root;
    while (3 分) {
        i = 0;
        while (i < node->numKeys) {
            if (3 分) i++;
            else break;
        }
        node = node->childrens[i];
    }
    for(i = 0; i < node->numKeys; i++){
        if(node->keys[i] == key)
            return true;
    }
    return false;
}
```

#### 编程

Suppose that a string of English letters is encoded into a string of numbers. To be more specific, `A`-`Z` are encoded into `0`-`25`. Since it is not a prefix code, the decoded result may not be unique. For example, `1213407` can be decoded as `BCBDEAH`, `MBDEAH`, `BCNEAH`, `BVDEAH` or `MNEAH`. Note that `07` is not `7`, hence cannot be decoded as `H`.

Your job is to tell in how many different ways we can decode a numeric string.

### Format of function:

```c++
int Decode( char NumStr[] );
```

where `NumStr` is a string consisting of only the numbers `0`-`9`.

The function `Decode` is supposed to return the number of different ways we can decode `NumStr`.

**Since the answer might be super large, you only need to output the answer modulo 1000000007.**

### Sample program of judge:

```c++
#include <stdio.h>
#include <string.h>

#define MAXN 100
#define BASE 1000000007

int Decode( char NumStr[] );

int main()
{
    char NumStr[MAXN];

    scanf("%s", NumStr);
    printf("%d", Decode(NumStr));

    return 0;
}

/* Your function will be put here */
```

### Sample Input:

```
1213407
```

### Sample Output:

```
5
```
