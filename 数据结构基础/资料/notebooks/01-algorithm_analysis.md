# 算法分析

## 渐进符号

大O符号上界 T(N) = O(f(N)) T(N) <= c * f(N)
存在c 使得   c*fn > Tn   
大Ω符号 T(N) = Ω(f(N)) T(N) >= c * f(N)是下界

大Θ符号 T(N) = Θ(f(N)) T(N) = O(f(N)) && T(N) = Ω(f(N)) 是上界又是下界

小o符号 T(N) = o(f(N))   T(N)< c * f(N)

* T1(N) + T2(N) = max(O(f(N)), O(g(N))

* T1(N) * T2(N) = O(f(N) * g(N))

* 若 T(N) 为 k 次多项式，则 T(N) = Θ(N ^ k)

* log(k, N) = O(N)

## 最大子列问题

线性算法：从头向尾加和，若和小于零则从下一个位置重新开始。

## 时间复杂度分析

### 递归

递推公式，代入求值，忽略小量（丢弃或化常）
代码规范， = 两边要有空格。

O（N）上界 ，Ω（N）下界
sequential list 顺序表，用数组存储。


顺序表，插入删除最后一个快。
插入第一个，移动n个，插入最后一个，移动0个。查询复杂度为O（1）

双向链表，操作后部分快很多。
最好头节点 添加O（1）， 删除O（1）
最好尾节点 添加O（1）， 删除O（1）

判断题
算法主要为了分析时间复杂度和空间复杂度 √
fibonacci 数列， 计算Fn的时间复杂度 是N！。 错， 递归是2的n次，非递归是O（n）
顺序表长度N，delete第一个时间复杂度是O（1），插入最后一个时间复杂度是O（n）。错，插入或删除第一个，所有都需要移动，所以O（n）。插入和删除最后一个，O（1）。


add two polynomial
用类， 包装一个建立node函数，一个advancePolynominal 进入下一个。
先创建一个dummy，然后cur = dummy


链表反转： 复杂度为O（n），非递归。把当前的移动到 最前面。
1 2 3 4 5
2 1 3 4 5 
3 2 1 4 5  



## Stack


后缀表达式
1。遇到数字，入栈
2  遇到符号，从前面取出两个数计算
3  如果仅剩一个数，那就所求。否则，错误。



two stacks in one array
初始化，一个 －1，一个maxsize，这是top指向栈顶上一个地址的方法。top指向栈顶，就一个0，一个maxsize－1 。
如果指向栈顶push时要用++top， 否则用top++会导致top已经到了full的判断边界，但是maxsize处还没有写入。Isfull的判断应该是 top1比top2小1就return full 了，不是== 也不是大于。
如果指向栈顶上一个地址。那就是用top++，top1比top2大1，

## deque


deque的实现
1。怎么连接front和rear
可以把rear作为结尾，放数据。
front在作为dummy node
初始化方法就front malloc，然后rear =front，rear下一个=null
push方法，如果没数据（front == rear）， 那就rear = 新的结点。



￼
如果有数据，那就 在front－》next = 新节点。
pop方法，如果没数据就error，有数据，一个数据就相当于再初始化一次。多个数据，就相当于链表操作删除掉front－》next 。
Inject 方法， 没有数据，就和push一样
有数据，就相当于在链表末尾插入数据。
Eject方法， 没数据就error，有的话就相当于在链表末尾删除数据。




  pop  sequence
搞不懂为啥 5 6 4 3 7 2 1 不对
应该 进 1 到 5，然后pop，然后 进6， pop， pop，pop，进 7 pop， pop，pop 就可以了。
加一个 &&空栈
第二个 3 2 1 7 5 6 4 又错了
进 12 3 出

后来发现栈顶元素和datam比较即可，而不是递增的v和datam比较
为啥会少判断一行?
..我也不知道，反正进pta就ak 了。
还有就是，答案错误是因为，我输出的是yes，no，而不是YES， NO 我无语了。
陈越ppt有爆炸声的哈哈哈哈