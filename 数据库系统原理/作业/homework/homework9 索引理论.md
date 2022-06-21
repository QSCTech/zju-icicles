14.3  Construct a B+-tree for the following set of key values: (2, 3, 5, 7, 11, 17, 19, 23, 29, 31)  Assume that the tree is initially empty and values are added in ascending order. Construct B+-trees for the cases where the number of pointers that will fit in one node is as follows: 

a. Four 

4个指针,最多3个key,

分裂的时候左边3个右边2个

![image-20220515171921897](/Users/juyilin/Library/Application Support/typora-user-images/image-20220515171921897.png)

c. Eight

![image-20220515172241057](/Users/juyilin/Library/Application Support/typora-user-images/image-20220515172241057.png)

14.4

For each B+-tree of Exercise 14.3, show the form of the tree after each of the following series of operations: 对于练习 14.3 的每个 B+ 树，在以下每个系列操作之后显示树的形式：

对于第一个树

a. Insert 9. b. Insert 10. c. Insert 8. d. Delete 23. e. Delete 19

![DF090AAD-68E4-4713-BF81-0AF398B9D457](/Users/juyilin/Library/Containers/com.tencent.qq/Data/Library/Application Support/QQ/Users/1263810658/QQ/Temp.db/DF090AAD-68E4-4713-BF81-0AF398B9D457.png)

<img src="/Users/juyilin/Library/Application Support/typora-user-images/image-20220515193056186.png" alt="image-20220515193056186" style="zoom:50%;" />

![image-20220515193133541](/Users/juyilin/Library/Application Support/typora-user-images/image-20220515193133541.png)

![image-20220515193339584](/Users/juyilin/Library/Application Support/typora-user-images/image-20220515193339584.png)

非叶子节点只有1个是不行的, 但是叶节点只有一个是可以的.

![image-20220515193529903](/Users/juyilin/Library/Application Support/typora-user-images/image-20220515193529903.png)

会从右边的节点中分一个出来.

对于第二个树  degree = 6

a. Insert 9. b. Insert 10. c. Insert 8. d. Delete 23. e. Delete 19

![image-20220515194111247](/Users/juyilin/Library/Application Support/typora-user-images/image-20220515194111247.png)

![image-20220515194130263](/Users/juyilin/Library/Application Support/typora-user-images/image-20220515194130263.png)

![C97DE9FB-B432-4EA0-A438-47C87A899AE2](/Users/juyilin/Library/Containers/com.tencent.qq/Data/Library/Application Support/QQ/Users/1263810658/QQ/Temp.db/C97DE9FB-B432-4EA0-A438-47C87A899AE2.png)

![image-20220515194237971](/Users/juyilin/Library/Application Support/typora-user-images/image-20220515194237971.png)

delete 23 和delete19 合并了.

对于max degree = 8 , 

其实就是在左边加入, 在右边删除, 没有分裂的操作. 不再画图.

14.11

In write-optimized trees such as the LSM tree or the stepped-merge index, entries in one level are merged into the next level only when the level is full. Suggest how this policy can be changed to improve read performance during periods when there are many reads but no updates.

在 LSM 树或步进合并索引等写优化树中，只有在该级别已满时，才会将一个级别中的条目合并到下一个级别。 如果读取次数多但没有update期间的, 如何更改此策略以提高读取性能



24.10

The stepped merge variant of the LSM tree allows multiple trees per level. What are the tradeoffs in having more trees per level?

LSM树的阶梯式合并变体允许每层有多个树。每层有更多的树有什么权衡？

 优点: 树更多,  一级可以放的也更多, merge 的次数就更少. 

缺点是: merge 的时候时间更久, 然后总共占用的空间也更多.
