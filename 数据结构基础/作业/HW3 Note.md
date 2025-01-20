### hw3:

2-1

Push 5 characters `ooops` onto a stack. In how many different ways that we can pop these characters and still obtain `ooops`?

>  p和s的顺序必须是push p, pop p, push s ,pop s
>
> 但是3个o可以有五种, (p as push, q as pop) ,pppqqq , ppqqpq, ppqpqq, pqppqq , pqpqpq

2-2

Represent a queue by a singly linked list. Given the current status of the linked list as `1->2->3` where `x->y` means `y` is linked after `x`. Now if `4` is enqueued and then a dequeue is done, the resulting status must be:

> Enqueue means chaining aother element to the end of the list,
>
> Dequeue means removes the first element of the list.

2-3

Suppose that an array of size 6 is used to store a circular queue, and the values of `front` and `rear` are 0 and 4, respectively. Now after 2 dequeues and 2 enqueues, what will the values of `front` and `rear` be?

> In circular queue:
>
> Rear = 0, front = 1
>
> Empty: Rear = front-1
>
> When enqueue, rear ++
>
> When dequeue,  front++

2-4

Suppose that all the integer operands are stored in the stack *S*1, and all the operators in the other stack *S*2. The function `F()` does the following operations sequentially:

- (1) Pop two operands `a` and `b` from *S*1;
- (2) Pop one operator `op` from *S*2;
- (3) Calculate `b op a`; and
- (4) Push the result back to *S*1.

Now given { 5, 8, 3, 2 } in *S*1 (where 2 is at the top), and { `*`, `-`, `+` } in *S*2 (where `+` is at the top). What is remained at the top of *S*1 after `F()` is executed 3 times?

> 1st
>
> S1:5,8,5 / S2:*, -
>
> 2nd
>
> S1:5, 3 / S2: *
>
> 3rd
>
> S1:15



### Pop sequence:

```c++
//use a stack with fixed size;
//naturally push on stack from 1 to n
//if causes stackoverflow, it's impossible to generate such sequence
//check if the stack.top equals the sequence[i]
//if equal, pop, until different, then push again.
//e.g 4,5

//the push is determined, and the sequence is determined, meaning the whole process is determined.
checked:['1',4,2,3,5]
stack:[1]
---
checked:[1,'4',2,3,5]
stack:[2] 
---
checked:[1,'4',2,3,5]
stack:[2] 
---
checked:[1,'4',2,3,5]
stack:[2,3]
---
checked:[1,'4',2,3,5]
stack:[2,3,4]
---
checked:[1,4,'2',3,5]
stack:[2,3]
---
checked:[1,4,'2',3,5]
stack:[2,3,4]
---
checked:[1,4,'2',3,5]
stack:[2,3,4,5]

---
//it's impossible to output the '2'
---
checked:['1',3,4,2,5]
stack:[1]
---
checked:[1,'3',4,2,5]
stack:[2] 
---
checked:[1,'3',4,2,5]
stack:[2,3] 
---
checked:[1,3,'4',2,5]
stack:[2,4]
---
checked:[1,3,4,'2',5]
stack:[2]
---
checked:[1,3,4,2,'5']
stack:[5]
---
checked:[1,3,4,2,'5']
stack:[]
//all sequence can be generated.
```



