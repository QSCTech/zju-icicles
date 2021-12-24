### 2.1

In a max-heap with *n* (>1) elements, the array index of the minimum key may be __.

> A:1
>
> Wrong: it’s the largest
>
> B:floor(n/2)-1
>
> Wrong: 2*(floor(n/2)-1)<n, it has a left child
>
> C:floor(n/2)
>
> Wrong: It has a left child
>
> D:floor(n/2)+2
>
> Correct: it doesn’t have any child

### 2.2

### Build Heap:

* Iterative insertion (worst case nlogn)

* Linear heap insertion: A bottom up heapify process

  * Bottom up(from non-leaf nodes to root), right to left recursively call heapify up
  * A divide and conquer method
  * https://www.youtube.com/watch?v=mnSMdTPBG1U&list=PLLuMmzMTgVK5Hy1qcWYZcd7wVQQ1v0AjX

  ![image-20211027114847539](https://i.loli.net/2021/10/27/eJu63hrVLFwqyNH.png)