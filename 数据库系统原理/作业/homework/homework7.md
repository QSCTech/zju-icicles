7.1, 

Suppose that we decompose the schema R = (A, B, C, D, E) into 

(A, B, C) (A, D, E). 

Show that this decomposition is a lossless decomposition if the following set F of functional dependencies holds: 

A → BC 

CD → E 

B → D 

E → A

怎么证明是无损分解?

R1 和R2交集是A, A-》B, A-〉 C,  所以A是R1的super key. 所以是无损连接.

答案：

同上。



7.3, 

Explain how functional dependencies can be used to indicate the following: 

• A one-to-one relationship set exists between entity sets student and instructor. 

• A many-to-one relationship set exists between entity sets student and instructor.

答: 

F1 = {student ->instructor , instructor -> student}

F2 = {instructor ->student}

答案：  一对一，同样的值 instructor 有同样的student。

多对一， 同样的student 有一样的instructor。多个stu也有一样的instructor。



7.21, 

Give a lossless decomposition into BCNF of schema R of Exercise 7.1

答: 

B->D. 是非平凡的,而且B不是superkey, 所以要分解.把D作为ß拆出R, 留下B, B在两边都有. 这样就可以得到.

{(A,B,C,E), (B,D)}是BCNF的.

B是R2的超码, =》无损的.





7.22, 

Give a lossless, dependency-preserving decomposition into 3NF of schema R of Exercise 7.1.

答: 

7.1给出的函数依赖, 是一个正则覆盖. 

所以可以根据正则覆盖直接分解

R = {(A,B,C) , (C,D,E) , (B,D), (E,A) } (A,B,C)  包含一个候选吗, 所以是无损的. 依赖保持, 3NF.





7.29

Show that the following decomposition of the schema R of Exercise 7.1 is not a lossless decomposition: 

(A, B, C) (C, D, E). Hint: Give an example of a relation r(R) such that ΠA, B, C (r) ⋈ ΠC, D, E (r) ≠ r

答: 

就是举例, C一样的, 两边都不一样, 连起来就会有多个.

比如 

R

a b c d e 

a1 b1 c1 d1 e1

a2 b2 c1 d2 e2

分解之后

R1

a b c 

a1 b1 c1 

a2 b2 c1 

R2 

c d e 

 c1 d1 e1

c1 d2 e2

自然连接之后

a b c d e 

a1 b1 c1 d1 e1

a1 b1 c1 d2 e2

a2 b2 c1 d2 e2

a1 b1  c1 d2 e2 

就多了a1 b1  c1 d2 e2. a1 b1 c1 d2 e2 

所以是有损连接
