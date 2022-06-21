17.6

Consider the precedence graph of Figure 17.16. Is the corresponding schedule conflict serializable? Explain your answer.

这是一个可串行化的schedule,  因为没有环.

可以通过拓扑排序来获得schedule, 比如T1, T2, T3,T4,T5

17.7

What is a cascadeless schedule? Why is cascadelessness of schedules desirable? Are there any circumstances under which it would be desirable to allow noncascadeless schedules? Explain your answer.

cascadeless schedule, 不允许cascading rollback,事务Tj读的时候如果Ti之前写了, 那么会阻塞直到Ti提交.

所有cascadeless schedule都是可恢复的.

好处是一个事务abort不会导致其他的回滚.

缺点是并发性差.

如果failures 很少, 那么我们应该允许 noncascadeless schedules..



17.12

List the ACID properties. Explain the usefulness of each.

A : atomic。原子性,  事务要么成功, 要么失败全部回滚, 不会有中间态. 

C。  consistency , 一致性. A转账到B, A+B的总金额不变.

I。isolation。隔离性, 每个事务的操作对于其他事务应该是不可见的.

D。durable , 持久性, 事务的操作在crash之后应该是可以恢复的.
