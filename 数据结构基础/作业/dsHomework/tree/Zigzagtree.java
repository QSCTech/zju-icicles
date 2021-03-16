package dshomewrok;
import java.util.*;
/*ZigZagging on a Tree


*/
public class Zigzagtree {
	public static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
        TreeNode(int x) {
            val = x;
        }
    }
	 private static int find(int[] array, int v) {
	        for (int i = 0; i < array.length; i++) {
	            if (array[i] == v) {
	                return i;
	            }
	        }
	        return -1;
	 }
	public static void main(String[] args) {
		int n = 0;
		int i = 0,j = 0;
	    Scanner sc = new Scanner(System.in);
	    n = sc.nextInt();
		int[] arr1,arr2;
		arr1 = new int[n];  // inorder
		arr2 = new int[n];  // postorder
	    for(i = 0;i < arr1.length;i++) { 
			arr1[i] = sc.nextInt();
		}
	    for(i = 0;i < arr2.length;i++) {
			arr2[i] = sc.nextInt();
		}
	    sc.close();
	    TreeNode root1 = BuildTree(arr1,arr2);
	    
	}
	/*build a Tree from postorder and inorder
	后序遍历的最后一个数为根结点，根据这个根结点来划分中序遍历，将其分为左子树和右子树
	②确定左右子树的中序遍历和后遍历中的界限,中序从0 - root为左, root+1 到最后为右. 后序0-root为左,root到postOrder.length-1 为右.
	③递归调用
	*/
	public static TreeNode BuildTree(int[] inOrder, int[] postOrder ) {
		
		if(postOrder.length == 0) {
			return null;
		}
		if(postOrder.length == 1) {
			TreeNode tmp = new TreeNode(postOrder[postOrder.length-1]);
			return tmp;
		}
		
		TreeNode root = new TreeNode(postOrder[postOrder.length-1]);  //先判断特殊,再new 一个.
		int rootpos = find(inOrder,root.val);
		int[] leftInorder = Arrays.copyOfRange(inOrder, 0, rootpos);  //copyOfRange 包括0 不包括rootpos.
		int[] rightInorder = Arrays.copyOfRange(inOrder, rootpos+1, inOrder.length);
		//System.out.println(rootpos);
		//System.out.println(Arrays.toString(rightInorder));
		//System.out.println(Arrays.toString(leftInorder)); //不能直接打印数组要tostring
		
		int[] leftPostorder = Arrays.copyOfRange(postOrder, 0, rootpos);
		int[] rightPostorder = Arrays.copyOfRange(postOrder, rootpos, postOrder.length-1);;
		//System.out.println(Arrays.toString(leftPostorder));
		//System.out.println(Arrays.toString(rightPostorder));
		
		root.left = BuildTree(leftInorder,leftPostorder);
		root.right = BuildTree(rightInorder,rightPostorder);

		return root;
	}
	
	
	/*要进行层次遍历，需要建立一个循环队列。先将二叉树头结点入队列，然后出队列，访问该结点，如果它有左子树
	则将左子树的根结点入队:如果它有右子树，则将右子树的根结点入队。然后出队列，对出队结点访问，如此反复，直到队列为空为止。
	z字形层次遍历是对层次遍历加上了一个限制条件（即相邻层，从左到右的遍历顺序相反），
	我们取queue大小,就是上一层的结点数. for循环把这一层都加入进去,如果奇数层就第一个结点开始(因为上一层是偶数)先加右再加左.
	如果偶数层就最后结点开始(因为上一层是奇数)先加左再加右.
	一层结束深度增加,同时用一个栈,因为遍历下一层的数据 和输出这一层的数据  是刚好相反的..
	data  arraylist是因为他最后不要空格, 所以全部保存了再输出. 不然stack其实就有正确答案了,最后多一个空格.
	*/
	
	public static void zigzagorder(JudgeRedBlackTree.TreeNode root ) {
		ArrayDeque<JudgeRedBlackTree.TreeNode> queue = new ArrayDeque<JudgeRedBlackTree.TreeNode>(32);
		ArrayList<Integer> data = new ArrayList<Integer>(32);  //no int but Integer
		JudgeRedBlackTree.TreeNode temp = root;
		Stack<JudgeRedBlackTree.TreeNode> res = new Stack<JudgeRedBlackTree.TreeNode>(); // 就是把他
		queue.add(temp);
		int depth = 0 ,i = 0;
		while(!queue.isEmpty()){
			int size = queue.size();
			for(i =0;i<size;i++) {
				if(depth %2 == 0) {
					temp = queue.pollLast(); 
					if(temp.left != null) {
						queue.addFirst(temp.left);
					}
					
					if(temp.right != null){
						queue.addFirst(temp.right);
					}
				}
				else {
					temp = queue.poll(); 
					if(temp.right != null){
						queue.add(temp.right);
					}
					if(temp.left != null) {
						queue.add(temp.left);
					}
				}
				res.push(temp);
			}
			while(!res.empty())  
				data.add(res.pop().val);
			depth ++;
		}
		for(i = 0;i<data.size()-1;i++) {
			System.out.print(data.get(i)+" ");
		}
		System.out.print(data.get(i));
	}

	
}
