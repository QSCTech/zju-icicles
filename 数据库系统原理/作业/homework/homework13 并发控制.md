18.1

Show that the two-phase locking protocol ensures conflict serializability and that transactions can be serialized according to their lock points.

假设两阶段所并不保证可序列化，那么就存在T0,T1::Tn-1这样遵循 2PL 而且非可序列化的时间表。

一个非可序列化的时间表意味着在前序图中有环，而我们将证明2PL 不会产生环。 

在不丧失一般性的前提下，假设以下的环存在于前序图中：T0T1T2...Tn-1 T0.让我们来看看Ti 获得最后一个锁的时间ai（即Ti的lock point）

a0 < a1 < a2 < ... < an-1<a0

 所以a0<a0矛盾， 所以不存在环。

在这个过程中，Ti Tj,i<j, lock point顺序也就是拓扑排序 顺序，而lock point顺序是序列化的。所以事务可以按lock point串行化。

18.2

Consider the following two transactions: 

```
T34: read(A); 
read(B); 
if A = 0 then B := B + 1; 
write(B). 
T35: read(B);
read(A); 
if B = 0 then A := A + 1; 
write(A). 
```

Add lock and unlock instructions to transactions T31 and T32 so that they observe the two-phase locking protocol. Can the execution of these transactions result in a deadlock?

```
T34
lock-S(A)
read(A)
lock-X(B)
read(B)
if A = 0
then B:= B+1
write(B)
unlock(A)
unlock(B)
T35
lock-S(B)
read(B)
lock-X(A)
read(A)
if A = 0
then B:= B+1
write(A)
unlock(B)
unlock(A)
```

可能会死锁， 

| T31       | T32       |
| --------- | --------- |
| lock-S(A) |           |
|           | lock-S(B) |
|           | read(B)   |
| read(A)   |           |
| lock-X(B) |           |
|           | lock-X(A) |

如上面的顺序操作就会死锁。

18.7

Consider a database system that includes an atomic increment operation, in addition to the read and write operations. Let V be the value of data item X. The operation increment(X) by C

sets the value of X to V + C in an atomic step. The value of X is not available to the transaction unless the latter executes a read(X). Assume that increment operations lock the item in increment mode using the compatibility matrix in Figure 18.25. 

a. Show that, if all transactions lock the data that they access in the corresponding mode, then two-phase locking ensures serializability. 

b. Show that the inclusion of increment mode locks allows for increased concurrency

a.可序列化通过观察两个事务有一个I mode锁on the same item来显示，其increment操作是可以交换的，就像读操作一样。然而，任何冲突操作必须按照对应事务的lock点的顺序序列化。

b。

increment lock mode与它本身允许多个扩增机构同时进行扩增兼容，从而改进了协议的并发性。 没有这种模式，一个想要增加数据值的事务必须对这个数据项采取exclusive  mode。 exclusive lock 是不兼容的， 会增加锁的等待时间， 阻碍整个并发过程。

总的来说， 增加true entries 在兼容性矩阵中可以增加并发性和吞吐量。

18.18

Most implementations of database systems use strict two-phase locking. Suggest three reasons for the popularity of this protocol.

严格两阶段锁（strict 2PL）：transaction直到执行结束（commit/abort）后才统一释放所有的锁。

1. 这种算法保证了strictness，避免了一个transaction abort就导致其他transaction产生cascading abort。 rollback少。
2. 比较容易实现
3. 并发度不算太小。





