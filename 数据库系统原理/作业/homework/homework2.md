2.12



Consider the relational database of Figure 2.14. Give an expression in the relational algebra to express each of the following queries: 

a. Find the names of all employees who work for “First Bank Corporation”. 

b. Find the names and cities of residence of all employees who work for “First Bank Corporation”. 

c. Find the names, street address, and cities of residence of all employees who work for “First Bank Corporation” and earn more than $10,000.

![image-20220302132350419](C:\Users\12638\AppData\Roaming\Typora\typora-user-images\image-20220302132350419.png)

2.14

List two reasons why null values might be introduced into the database.

1. 因为实际上现在没有这个值
2. 或者现在不知道这个值



2.15

Discuss the relative merits of procedural and nonprocedural languages.

过程式的好处:

**当描述的目标变复杂时，声明式语言也不可避免变得更命令式，通过描述过程来描述更多细节**

过程式的坏处:

1. 代码量大
2. 语义比较复杂

反之就是非过程式的好处:

代码量小, 语义简单. 大大减轻了用户负担，而且有利于提高数据独立性. 用户无须了解存取路径，存取路径的选择以及SQL语句的操作过程由系统自动完成

它还隐藏了数据库引擎的实现细节，这使得数据库系统可以在无需对查询做任何更改的情况下进行性能提升。

所以SQL 非过程化,是声明式.  用户无需担心如何评估查询；这不仅减少了编程工作量，而且实际上，在大多数情况下，查询优化器比通过反复试验的程序员能够更好地选择最佳的评估查询方法。

最后，声明式语言往往适合并行执行. 命令代码很难在多个核心和多个机器之间并行化，因为它指定了指令必须以特定顺序执行。声明式语言更具有并行执行的潜力，因为它们仅指定结果的模式，而不指定用于确定结果的算法。在适当情况下，数据库可以自由使用查询语言的并行实现。



reference:https://github.com/Vonng/ddia/blob/master/ch2.md 