15.6

Consider the bank database of Figure 15.14, where the primary keys are underlined. Suppose that a B+-tree index on branch city is available on relation branch, and that no other index is available. List different ways to handle the following selections that involve negation: 

a. σ ¬(branch city<“Brooklyn”)(branch) 

定位到第一行branch_city字段有Brooklyn , 然后往下找到所有 

b. σ ¬(branch city=“Brooklyn”)(branch)

索引没有任何作用, 找到所有除了branch_city字段=brooklyn的 行.

 c. σ ¬(branch city<“Brooklyn” ∨ assets<5000)(branch)

This query is equivalent to the query σ(branch city≥′Brooklyn′ ∧ assets>5000)(branch) 

找到布鲁克林, 然后利用pointer 链可以找到所有branch citycity≥′Brooklyn′ 的行 ,  同时判断assets >=5000的结果

16.5

Consider the relations r1(A, B, C), r2(C, D, E), and r3(E, F), with primary keys A, C, and E, respectively. Assume that r1 has 1000 tuples, r2 has 1500 tuples, and r3 has 750 tuples. Estimate the size of r1 ⋈ r2 ⋈ r3, and give an efficient strategy for computing the join

考虑关系r1(A, B, C), r2(C, D, E), 和r3(E, F), 分别具有主键A, C, 和E。假设r1有1000行，r2有1500行，r3有750行。估计r1⋈r2⋈r3的大小，并给出计算连接的有效策略。

因为有交换律, 所以先join 哪个都是可以的.

比如先r1 自然连接r2 ,   最多产生1000行的关系, 因为C是r2的key.

然后自然连接r3, 因为连接的E是r3的key, 所以最后也是最多1000行. 

有效策略:

在关系r2的属性C和r3的E上建立一个索引.

遍历r1, 然后根据索引从r2中寻找对应的C,  然后根据r2对应的那一行, 从r3中寻找对应的E.                       

16.16

Suppose that a B+-tree index on (dept name, building) is available on relation department. What would be the best way to handle the following selection? 

σ(building < “Watson”) ∧ (budget < 55000) ∧ (dept name = “Music”)(department)

首先定位到第一个dept name = “Music”, 然后 按pointer链 取出下面所有 building < “Watson” 的, 对于每个tuple , 判断是否budget < 55000.

```
branch(branch name, branch city, assets) 
customer (customer name, customer street, customer city) 
loan (loan number, branch name, amount) 
borrower (customer name, loan number)
account (account number, branch name, balance ) 
depositor (customer name, account number) 

Figure 16.9 Banking database.
```

16.20

Explain how to use a histogram to estimate the size of a selection of the form σA≤v(r).

解释如何使用直方图来估计形式为σ A≤v  (r)的选择的大小。



如果知道最小值和最大值就是 nr *(v-min)/(max-min)

那么根据直方图, 可以定位v所在的取件, 然后修改估算式子, 用区间的频度

就是nr*(v所在区间到最小区间的频率之和)/(所有区间的频率之和)
