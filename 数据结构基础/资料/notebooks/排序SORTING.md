# 排序SORTING

hash排序不通过比较, 

算法稳定性：
插入排序：稳定 , 因为一个个
希尔排序：不稳定, 因为交换
快速排序：不稳定 , 因为排序后交换
堆排序：不稳定  ,直接拉到最上面交换
归并排序：稳定 ,指针一个个移动
基数排序：稳定

### 插入排序

从第一个元素开始，该元素可以认为已经被排序;

取出下一个元素，在已经排序的元素序列中从后向前扫描；

如果该元素（已排序）大于新元素，将该元素的值赋值给新元素；循环此步骤,直到不大于新元素;

一趟出来前面变为有序,再选取下一个元素;

把A[j-1] 往后移动, 插入

最坏情况O(N^2)

最好 线性

一个array中平均的逆序对是 N(N-1)/4 个, 最多 N(N-1)/2个.

### SHELLsort

希尔排序(Shell's Sort)是插入排序的一种又称“缩小增量排序”（Diminishing Increment Sort），
是直接插入排序算法的一种更高效的改进版本。希尔排序是非稳定排序算法。
由于多次插入排序，我们知道一次插入排序是稳定的，不会改变相同元素的相对顺序，但在不同的插入排序过程中，相同的元素可能在各自的插入排序中移动，最后其稳定性就会被打乱，所以shell排序是不稳定的。

过程： 第一个和+5交换，  然后看看+10 交换，然后看看+15 往前交换  到底了

然后第二个，  加4往前交换，  然后看看+8往前交换。
也就是所有距离为d1的倍数的记录放在同一个组中。先在各组内进行直接插入排序；

定义增量 h1 < h2 <  ... <ht

hk-sort at each phase 

h5  , 一次五个五个移动

注意不能推翻之前步长做的sort.

最坏 O(N^2)

Hibbard 增量序列.

最坏O( N^(3/2) ) 

平均O( N^(5/4) ) 

#### 优劣

**不需要大量的辅助空间，和归并排序一样容易实现。**希尔排序是基于插入排序的一种算法， 在此算法基础之上增加了一个新的特性，提高了效率。
希尔排序时间复杂度为O( N^(5/4) )，希尔排序时间复杂度的下界是n*log2n。希尔排序没有快速排序算法快 O(n(logn))，
因此中等大小规模表现良好，对规模非常大的数据排序不是最优选择。但是比O( n^2 )复杂度的算法快得多。并且希尔排序非常容易实现.
算法代码短而简单。 此外，希尔算法在最坏的情况下和平均情况下执行效率相差不是很多，与此同时快速排序在最坏的情况下执行的效率会非常差。
专家们提倡，几乎任何排序工作在开始时都可以用希尔排序，若在实际使用中证明它不够快，再改成快速排序这样更高级的排序算法. 



### heapsort

堆排序空间为O（1）
就是提取最大， 然后堆向下， 然后提取最大， 然后堆向下。

不需要额外的空间,  先build heap

```c
  for(i = N/2;i>=0; i-- )
      PercDown(A,i,N);// build heap
 for(i= n-1; i>0 ; i--){
     swap(A[0],A[i]);// deletemax 取出来就.
     PercDown(A,0,i)
 }
```

时间复杂度O(N loglogN)



### mergesort 归并排序

递归分成小任务, 然后合起来.  需要O(N) 额外空间   作为临时数组

 time complexity : O(N)

```
void Msort{

Msort(前一半)  //递归不断拆成2个, 然后合起来. 

Msort(后一半) // T(N/2)

Merge(两个)  //O(N)

}
```



归并排序的效率达到了巅峰：时间复杂度为O(nlogn)，这是基于比较的排序算法所能达到的最高境界.
公式：T[n]=2T[n/2]+O(n);
最终得出结果为：T[n]=O(nlogn); 
因为不管元素在什么情况下都要做出这些步骤，所花销的时间是不变的，所以该算法的最优时间复杂度和最差时间复杂度以及平均复杂度是一致的：O（nlogn）。
$$
T(N ) = 2^k(N/2^k) +k*O(N)
= N*T(1) +logN*O(N)
=O(N+NlogN)
$$
也有iterative version. 



归并排序是一种稳定的算法（即在排序过程中大小相同的元素能够保持排序前的顺序，3212升序排序结果是1223，排序前后两个2的顺序不变），这一点在某些场景下至关重要
归并排序是最常用的外部排序方法（当待排序的记录放在外存上，内存装不下全部数据时，归并排序仍然适用.）在external sorting很有用. 例如 在把多个外存磁盘阵列 合起来读取到一个存储空间的算法.

#### 缺点：

拷贝比较慢, 而且需要额外的空间, 不适合internal sorting,  归并排序需要O(n)的辅助空间，而与之效率相同的快排和堆排分别需要O(logn)和O(1)的辅助空间，在同类算法中归并排序的空间复杂度略高

### quick sort

实践中最快的排序算法.

选取一个作为pivot ,

如果选到最大或者最小, 两轮后应该是两个或者三个分割点,  如果没有选到最大或者最小, 两轮后应该是三个分割点.

best case T(N ) =  O(N logN )

pivot = A[0]   is a wrong way 

a safe maneuver : pivot is a random  . but generation is time expensive 

median elminate wrong way 5% time. 

小数组 N<20 , insertion sort比quick sort 更快.  if(i+cutoff)< right  qsort  else qsort

快速排序， 首先第一个为pivot， 后面分为<pivot 和> pivot 的部分， 如果<pivot , 那就分到小于的一堆，如果> pivot ，那就分到大于的一堆。

 首先从后半部分开始，如果扫描到的值大于基准数据就让high减1  如果发现有元素比该基准数据的值小，就将high位置的值赋值给low位置 

然后开始从前往后扫描,如果扫描到的值小于基准数据就让low加1,如果发现有元素大于基准数据的值，就再将low位置的值赋值给high位置的值.



速度比较

If there are less than 20 inversions in an integer array, the Quick Sort will be the best method among Quick Sort, Heap Sort and Insertion Sort.

这样快排应该最快

快速排序在随机数据表现比堆排好。

虽说堆排和快排都是n log（n）级的，数据比较，堆排的常数是快排的2.5倍。

在非随机数据下，快排的就没有什么优势了，特别是全一样的数时，达到了n^2的上限

对于快速排序，有点就在于通过分治法从顶到底的渐进有序，选择的基准数使得分成的左右两个子序列长度越接近（即分区越平衡），快排的效率越高。反之，选择的数使分区不平衡，快排的效率就会降低。 
 回到问题，当序列渐进有序时，意味着大量元素已经处于有序状态，左边的数普遍比右边的小。对于**普通快排**，默认选择左边第一个元素作为基准数，这就导致小与基准的数会相当少，而大于基准的数相当多，造成分区不平衡的问题，普通排序就会退化，严重的将退化成O(n^2)。所以对其改进：不再默认选择第一个数，而是随机选一个数作为基准，这样的快排称为**随机普通快排**。 
 实现上，随机普通快排随机选一个数与第一个数交换，然后在将第一个数作为基准（这样代码好写），进行普通快排即可。所以随机普通快排只是对普通快排进行了一下预处理而已。

问题1：对于渐进有序的数组，效率很差 
 改进：随机选择基准。得到**随机化快速排序**。

问题2：对于含有大量重复元素的序列，即使是随机化快排效率也很差 
 于是再次改进，得到 
 双路快排

三路快排： 从两端向中间挺近，设立三个区：小与区，等于区，大于区

### Sorting 大结构

不交换所有变量而是交换指向结构的指针.

table sort.



### a general lower bound for sorting

Ω(N logN)

N个元素, N!个不同结果, 

thus, 决策树 必须有N! leaves 

高度是K, 
$$
N! <= 2^{k-1}
$$
=>  k>= log(N!)+1
$$
N! >= (N/2)^{(N/2)}   =>  log(N!) >= (N/2)log{(N/2)}
$$


### bucket sort and radix sort

bucket sort 建1000个桶 , 

radix sort 建10个桶, 按最低位排序.  然后按十位排序. 按百位 T= O(P+B) P是pass  = 3 pass,

B 是bucket 的数量, B =  10 . 在线性时间内排序.

MSD  most significant digit sort  4个桶,每个桶可以独立排

LSD 必须在前一次排序基础上排序.

LSD总是比MSD快吗? 不一定



#### 基数排序(radix sort）

是属于“分配式排序”（distribution sort），又称“桶子法”（bucket sort）或bin sort，顾名思义，它是透过键值的部份资讯，将要排序的元素分配至某些“桶”中，藉以达到排序的作用，基数排序法是属于稳定性的排序，其时间复杂度为[*O ( d(n+radix ) )*](http://blog.csdn.net/wu_lai_314/article/details/8475237)，其中r为所采取的基数，而m为堆数，在某些时候，基数排序法的效率高于其它的比较性排序法（比较性排序法的时间复杂度下限是O（n log n））。

基数排序的方式可以采用LSD（Least sgnificant digital）或MSD（Most sgnificant digital），LSD的排序方式由键值的最右边开始，而MSD则相反，由键值的最左边开始。 LSD的基数排序适用于位数小的数列，如果位数多的话，使用MSD的效率会比较好，MSD的方式恰与LSD相反，是由高位数为基底开始进行分配，其他的演算方式则都相同。 

基数排序
 它是一种稳定的排序算法，但有一定的局限性：
 　1、关键字可分解。
 　2、记录的关键字位数较少，如果密集更好
 　3、如果是数字时，最好是无符号的，否则将增加相应的映射复杂度，可先将其正负分开排序。

 

 

### 作业:

During the sorting, processing every element which is not yet at its final position is called a "run". Which of the following cannot be the result after the second run of quicksort?

只需要掌握一点就可以解出这个问题：每趟排序就有一个元素排在了最终的位置上。那么就是说，第n趟结束，至少有n个元素已经排在了最终的位置上。

每轮当分割点的元素,一定会在正确的位置.

所以我们把最终排序结果写出来：2,3,4,5,6,7,9去与每一项做比较即可快速判断。

 快排最理想的情况, 就是每轮都选到中间点,  这样两轮过后会有三个分割点, 

如果选择了最值, 会有两个或三个分割点.

D没有选到最值, 又没有三个分割点, 是不可能的. 

When running internal sorting, if merge sort is chosen instead of insertion sort, the possible reason should be:

1. The     code of merge sort is shorter X insertion sort 更短。 
2. Merge     sort takes less space X 不需要空间
3. Merge     sort runs faster 对

Among the following sorting methods, which ones will be slowed down if we store the elements in a linked structure instead of a sequential structure?

 

#### external sorting

考试不考,作为补充资料.



#### polyphase merge

k way merging using k+1 tapes.

#### replacement selection



