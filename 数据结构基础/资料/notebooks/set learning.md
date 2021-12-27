# disjoint_set不相交集



用于记录集合中的等价类。

##### 1 综述

Representation: tree, node with parent link

Union improvement: union-by-size, union-by-height

自反性 reflexivity 

令C={（x,y）|baix、y属于A}，设D是C的某非空子集，如果（x，y）属于D，则称x，y有（由D规定的）关系，记为x ~ y。(符号（*,*）表示两者组成的有序对）。如果（x，x）属于D总成立，则称那个由D规定的关系具有自反性。

若对所有的 a，b，c 属于 X，下述语句保持有效，则集合 X 上的二元关系 R 是传递的transitive：「若a 关系到 b 且 b 关系到 c， 则 a 关系到 c。

symmetric

xRy真 , yRx就必真，则称关系R为类k中对称的关系

如果xRy真  yRx就必假， 则称关系R为类K中反对称的关系（反对称关系）

##### 2 find 

```C
for(;s[x]>0;x = s[x]);
return x;
```



##### 3 合并 

找到根,一样的根是在同一个等价类中.

naive合并, 让一个根指向另一个根,两个树合并.   直接将root2的根改为root1，单次find最坏是O(N)

```C
S[Rt2] = Rt1
S[4] = 10
```



Union  by rank(height)

我们追踪每棵树的高度而不是大小，并总让浅的树成为深的树的子树。可以看出只有两颗树的高度相同时树的高度才会增加。当然我们实际上也是存储树的高度的负值.保证树的深度最多是O(logN) 

```C
Void SetUnion(Disjset  S, SetType Root1, SetType  Root2)
{
       if (S[Root2] < S[Root1]  /* Root2 is deeper set  */
            S[Root1] = Root2;      /* Make Root2 new root  */
       else 
       {
          if ( S[Root1] = = S[Root2])  /* Same height   */
                S[Root1] --;                     /* so update    */
          S[Root2] = Root1;
        }
 }

```



##### 4 Smart Union 算法

```C
s[root] = -size;
```

Union by size  函数，Union函数用来将两个节点的父节点组成连接在一起，连接的原则是size较小的树连接到size较大的树上。按大小合并  .，可以证明，任何节点的深度不会超过logN，单次find操作最坏为O(logN)

我们总是让较小的树成为较大的树的子树。 实现起来的话我们让根节点保存节点数目的负值，然后每次合并之前比较大小。初始时只有一个节点，所以初始值设为-1。

```C
void UF::unionBySize(int root1,root2){
    if(s[root2] > s[root1])  //因为是负值，所以说明root1更大
        s[root1] += s[root2];
        s[root2] = root1;
    else {
        s[root2] += s[root1];
        s[root1] = root2;
    }
}
```



时间复杂度  M次find 和N次Union
$$
O(N+Mlog_2N)
$$


##### 5 路径压缩

把路径上的结点直接指向root ,递归的算法如下

```c
SetType Find(int X,DisjSet S)
{if(s[x] <= 0) return X;
else return S[x] = Find(S[X],S);
}
```

非递归的算法也可以,用循环. 

```C
Find ( ElementType  X, DisjSet  S )
{   ElementType  root,  trail,  lead;
    for ( root = X; S[ root ] > 0; root = S[ root ] )
        ;  /* find the root */
    for ( trail = X; trail != root; trail = lead ) {
       lead = S[ trail ] ;   
       S[ trail ] = root ;   
    }  /* collapsing */
    return  root ;
}
```

Note:  not compatible with union-by-height 

##### 6 worst case for union by rank and path compression

 可以证明，使用按秩求并和路径压缩探测方法最坏情况下几乎是线性的，实际中一般一个较弱的结果是O(MlogN)。

