# Hash



符号表 symbol table = 字典, 编译器看看字典里类型. 比如int a.

不用把所有关键字都作为key,而是 存关键字的hash值作为key.

collision:  两个hash到一个key了.

元素个数n = 10, 

loading density factor λ = 10/(26*2)   26 是 bucket.  2 是slot个数.

hash 应该是 unbiased ,uniform, 最好每个概率相等. 



### 处理哈希碰撞（hash collision）的方法

#### 一 separate chaining 

每个key 有一个chain, 链接一个链表, create an empty table

```

申请
先申请thelists和tablesize.
tablesize = 一个素数
thelists = malloc(sizeof(list)* tablesize)
```

find a key from hash table ,最坏查找为O(n), 平均为O(1)

insert  插入操作的最坏是O(1),

删除最坏要O(1)

```
find// 计算了一次hash函数,速度要求高或许可以少调用一次hash.
如果find不到,那就
malloc (sizeof(struct ListNode));

L = H->TheLists[Hash(Key,H->tablesize)];
```

让loading density factor λ  = 1 ,也就是减少bucket空余, table size接近元素个数.



#### 解决方式二 open addressing开放寻址法

不产生一个list, 而是找另一个cell.  

```
while collision{
index = hash(key)+f(i);
如果table满了, break;
i++;
}

```

用来计算开放寻址中的探查序列的方法: 

- 线性探测器（Linear Probing）

linear probing( 探查性的)冲突了之后, 就放下一个, 下一个有了,再下一个.

线性探查. f(i) = c1 i; 从T[hash[k]]开始,到了T[m-1] 后, 再到T[0], 最后到T[hash[k]-1]

缺点是primary clustering ,也就是占用的不断变多,平均查找时间会不断增加.

但是删除了, 就搜索不到hash(key)了,怎么办?

一个办法是把这个位置放上deleted标签, 但这样查找时间会变化, 所以必须删除关键字的应用中, 往往还是用chaining 法.

- 二次探测法（Quadratic Probing）

平方探查 f(i) = c1 i^2+c2 i;

只要至少一半是空的,就一定能找到. 否则可能找不到空.

- 随机探测法
- 双散列（Double hashing）

双重散列, index = hash(key)+i* hash2(key);

第一个探查的为index = hash(key), 后面increment加偏移量 hash2(key).

比较接近理想的一致散列.

- 再哈希法rehashing

a insertion 失败, 或者half full 或者table reaches a certain load factor. 
 用rehashing. 

build another table 两倍大, scan down original hash table, use a new function to hash into new table.





- 建立一个公共溢出区



作业:

用于插入的探测序列预期数量大于linear probe方法中成功搜索的探测序列数量?the expected number of probes for insertions is greater than that for successful searches in linear probing method   不成功的探测数至多为 1/(1-λ) ;  插入最多为1/(1-λ) ;  成功的探测数至多为 ln(1/(1-\lambda))/(λ)



insertions are generally quicker than deletions in separate chaining method 对的. 插入就直接插入, 查找可能要找完整个table.

if the table size is prime and the table is at least half empty, a new element can always be inserted with quadratic probing

