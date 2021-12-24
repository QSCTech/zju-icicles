<img src="/Users/naoyuki/Library/Application%20Support/typora-user-images/image-20211219235340718.png" alt="image-20211219235340718" style="zoom:50%;" />

Quicksort is a recursive sorting method.

We choose a pivot, in each run, the element left to the pivot is smaller and the element right to the pivot is larger.

We keep pL and pR, starting from the left and right end of the array. If(pL==pR) we swap pivot with the intersection.

And after swap, we do this to the left of the pivot and right of the pivot. 

### 1.1 To sort *N* records by quick sort, the worst-case time complexity is *O*(*Nl**o**g*N).

No, the worst case of quick sort is N^2

The *i*th call does *O*(*n* − *i*) work to do the partition, and![\textstyle \sum _{i=0}^{n}(n-i)=O(n^{2})](https://wikimedia.org/api/rest_v1/media/math/render/svg/8829d4203c5b6319b5752064f10812e9aa8e3b20), so in that case quicksort takes *O*(*n*2) time. 

* It takes n-i steps to find out which elements are smaller and which elements are larger



### 1.2 During the sorting, processing every element which is not yet at its final position is called a "run". To sort a list of integers using quick sort, it may reduce the total number of recursions by processing the small partion first in each run.

No, This problem is to ask, what affects the recursion depth of the quicksort.

你会发现，递归深度只和pivot的选择有关，因为每次实际上只是找出了小于pivot的数字和大于pivot的数字，所以就算modify一下吮吸，也不影响最后这些位置和pivot的相对大小，如果pivot每次都选最大或最小，递归深度是最大的。



### 1.3 If there are less than 20 inversions in an integer array, the Quick Sort will be the best method among Quick Sort, Heap Sort and Insertion Sort.

No. Array with less inversions are great for insertion sort.



### 2.1 Solved: The key is after each run, it’s guaranteed to be at its final place, but its relative comparison depends on implementation<img src="/Users/naoyuki/Library/Application%20Support/typora-user-images/image-20211220002245029.png" alt="image-20211220002245029" style="zoom:50%;" />

A run menas “Every Element not yet at its final position”. After the first run, there will be one element sorted in its final place. The second run, there will be 1～2 elements at its final place. One in left to the original pivot and one in right to the original pivot.

* After the element is sorted, the right of the sorted element must be larger than the sorted element, the left must be smaller.

### 2.2

![image-20211220013626471](https://s2.loli.net/2021/12/20/BnSpGJQ4m93Z65u.png)

### D

### 2.3

### When running internal sorting, if merge sort is chosen instead of insertion sort, the possible reason should be:

1. The code of merge sort is shorter
2. Merge sort takes less space
3. Merge sort runs faster

3: as merge sort takes more space.

### 2.4

![image-20211220013841091](https://s2.loli.net/2021/12/20/DL19ZdHAJQw5kO2.png)

如果在链表中存储数据，变慢的操作是：访问第n个元素，变快的是插入

### 2.5

When selecting a sorting algorithm, which of the following factors must be taken into consideration besides the time and space complexities?

* I、the size of input data
* II、the structure used to store the data
* III、the stability of the algorithm
* IV、the initial condition of the data



I: small size using insertion

II: Don’t use heap sort for linked list

III: Don’t use unstable algorithm on array with the same key

IV: Don’t use insertion sort on large inversion array