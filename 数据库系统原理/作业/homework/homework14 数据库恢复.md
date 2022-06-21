19.1

Explain why log records for transactions on the undo-list must be processed in reverse order, whereas redo is performed in a forward direction

如果数据被update 了不止一次， 比如1 -》2， 2-》3。 如果undo 正向处理， 那么最后是2， 就不对了。 所以要反向。

如果有多个事务update数据， 那么正向处理，  最后就是最迟的那个事务的数据而不是最早的事务。 也是错的。

同上， 正向处理对于forward 最后是3， 是对的。 

19.2

Explain the purpose of the checkpoint mechanism. How often should checkpoints be performed? 

How does the frequency of checkpoints affect: 

• System performance when no failure occurs?  频率太高系统性能变慢。

• The time it takes to recover from a system crash?  可以减少recover时间

• The time it takes to recover from a media (disk) failure? 对disk crash 没有影响。  

搜索整个日志很费时间， all 事务要undo redo from the log。 在checkpoint之前的log 可以recover的时候不用搜索。

第二个原因是当stable storage 满了的时候清理log 

19.10

Explain the reasons why recovery of interactive transactions is more difficult to deal with than is recovery of batch transactions. Is there a simple way to deal with this difficulty? (Hint: Consider an automatic teller machine transaction in which cash is withdrawn.)

交互式更难， 因为有些是不可撤销的，irrevocable。

比如在事务的最后做所有的输出， 在中间abort了就不会有harm， 这就是batch的好处。

方法： 物理log 记录下来，  之后可以手动恢复。

19.21

Consider the log in Figure 19.5. Suppose there is a crash just before the log recordis written out. Explain what would happen during recovery。

redo 

1. redolist = T0，T1
2. 从checkpoint 开始进行redo
3. C= 600
4. T1 从redo list中 移除， 因为已经commit了
5. T2 加入， 因为T2 start了
6. A = 400
7. B = 2000

undo 阶段

1. 一开始T2， T0 
2. log 从后往前扫描
3. A = 500， 输出<T2, A, 500>
4. 输出T2 abort
5. B  =2000  输出<T0, B, 2000>
6. 输出T0 abort 

最后， A=500，  B =2000， C = 600 

log record 加入了：

```
<T2, A, 500>
<T2 abort>
<T0, B, 2000>
<T0 abort>
```

可以用 ARIES算法来优化， 去除冗余的record。

19.25

In the ARIES recovery algorithm:

a. If at the beginning of the analysis pass, a page is not in the checkpoint dirty page table, will we need to apply any redo records to it? Why? 

在checkpoint 之前的redo record 不需要apply。因为已经被刷到磁盘而且从dirtypage table移除。  然而， 可能checkpoint 之后又更新了， 分析过程结束后可能会出现在 dirtypage table。

b. What is RecLSN, and how is it used to minimize unnecessary redos?

RecLSN是DirtyPageTable中的一个条目，它反映了该页被添加到DirtyPageTable时的日志结束时的LSN。在ARIES算法的重做过程中，如果遇到的更新日志记录的LSN小于DirtyPageTable中的页面的RecLSN，那么该记录不会被重做，而是被跳过。此外，重做过程从RedoLSN开始，这是检查点DirtyPageTable中最早的RecLSN，因为更早的日志记录肯定不需要被重做。(如果检查点中没有脏页，RedoLSN被设置为检查点日志记录的LSN）。
