## HW4 Note:

1. There exists a binary tree with 2016 nodes in total, and with 16 nodes having only one child.

> 分析： 假设没有孩子的结点（叶结点）个数为n₀，只有一个孩子的结点（度为1的结点）个数为n₁，有两个孩子的结点（度为2的结点）个数为n₂。
> 则n₀+n₁+n₂=2016 ∵n₀=n₂+1（二叉树的性质：叶结点个数等于度为2的结点个数加1） ∴n₀+n₁+n₂=2016
> ⇨n₂+1+16+n₂=2016 ⇨2n₂=1999 n₂除不尽，所以答案错误。

------------------------------------------------
2. Given a tree of degree 3. Suppose that there are 3 nodes of degree 2 and 2 nodes of degree 3. Then the number of leaf nodes must be __8__.

>#edge = 4n3+3n2+2n1+n0/2
>
>#edge = n3+n2+n1+n0 -1



3. If a general tree *T* is converted into a binary tree *BT*, then which of the following *BT* traversals gives the same sequence as that of the post-order traversal of *T*?

![image-20211012161910295](https://i.loli.net/2021/10/12/IJD1QGa3CdFK746.png)

> Take the left tree for example:
>
> if(node->subtree)
>
> ​	goto subtree
>
> visit(node)

> Post-order traversal should be: k l e f b g c m h i j d a
>
> BT inorder traversal: l k e f b g c m h i j d a (k and l can be interchanged)

> Another explanation would be, in the post-order of T, root would always be the last one, and leftmost being the first. Last child of root being the second last.
>
> In the transformed BT, if it’s preorder or level-order, root would be first.
>
> if it’s post order, first child of root would be second last
>
> If inorder, problem solved.



4. Among the following threaded binary trees (the threads are represented by dotted curves), which one is the postorder threaded tree?

   #### Note: Thread is placed only when node has either left or right subtree.

   ![image-20211012170511966](https://i.loli.net/2021/10/12/NzODxeYMsXr6mCy.png)

| Predecessor | Node | Successor |
| ----------- | ---- | --------- |
| Head        | d    | b         |
| d           | b    | c         |
| b           | c    | a         |
| c           | a    | Head      |

Post-order: d b c a



### Binary Tree Isomorphism:

![image-20211012203930245](https://i.loli.net/2021/10/12/us7y5E9FPclS4h8.png)

```pseudocode
check(rootA==rootB)

//end case
if(!nodeA and !nodeB)
	return true
//one is end the other is not
else if(!nodeA or !nodeB)
	return false
//false case
else if(nodeA->data!=nodeB->data)
	return false


conditionA = isIsomorphic(rootA.left,rootB.left)&&isIsomorphic(rootA.right,rootB.right)

conditionB = 
isIsomorphic(rootA.left,rootB.right)&&isIsomorphic(rootA.right,rootB.left)

	return conditionA or conditionB
```



## Zigzag on a tree:

* Construct Binary

  * Check leetcode 106
  * PostOrder:(left),(right),root
  * Inorder:(left),root,(right)

  ```pseudocode
  build(node,ibegin,iend,pbegin,pend)
      root = postOrder.last
      leftTreeSize = iend-ibegin
      rightTreeSize = iend-getIndexInorder(root)
      root.left = build(ibegin,ibegin+leftTreeSize-1,pbegin,pend+leftTreeSize-1)
      root.right = build(ibegin,ibegin+rightTreeSize-1,pbegin+leftTreesize,pend-1)
      return root
  
  ```

* Level Order Traversal

  * Check leetcode 103
