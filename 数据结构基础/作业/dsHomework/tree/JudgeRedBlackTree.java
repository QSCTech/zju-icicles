package dshomewrok;
import java.util.*;

public class JudgeRedBlackTree {
	
	public static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
        TreeNode() {
        }
        TreeNode(int x) {
            val = x;
        }

    }

	public static void main(String[] args) {
		int n = 0;
		int i = 0,j = 0, k = 0,tmp = 0;
	    Scanner sc = new Scanner(System.in);
	    n = sc.nextInt();
	    TreeNode root1 = null; 
	    for(i = 0;i < n;i++) {  // judge n trees
	    	root1 = null;  
	    	k = sc.nextInt();   // k is number of the  tree's node
	    	for(j = 0;j < k;j++) {
	    		 tmp = sc.nextInt();
	    		 root1 = BuildTree(root1,tmp);
			}
//	    	System.out.println("build new tree finished");
	    	judge(root1);
	//    	System.out.println("judge new tree finished");
		}
	    sc.close();
	}
	
	/*build a Tree from x */
	public static TreeNode BuildTree(TreeNode root, int x) {
		if(root == null) {
			root = new TreeNode(x);
			root.left = null;
			root.right = null;
		}
		else if(Math.abs(x) < Math.abs(root.val)) {
			root.left = BuildTree(root.left, x);
		}
		else {
			root.right = BuildTree(root.right, x);
		}
		return root;
	}
	
	/* property 4, There can be no two consecutive red nodes on all paths from each leaf to the root) */
	public static Boolean Pro4(TreeNode root ) {
	//	System.out.println("judge property 4  begin");
		if(root == null) {
	//		System.out.println("pro4 is true ");
			return true;
		}
		if(root.val < 0) {   //if this node is red
	//		System.out.println("root.val = "+root.val);
			if( root.left != null ) {
	//			System.out.println("root.left.val = "+root.left.val);
				if(root.left.val < 0) return false;
			}
			if( root.right != null ) {
	//			System.out.println("root.right.val = "+root.right.val);
				if(root.right.val < 0) return false;
			}
	//		System.out.println(root.val+"red node is checked ");
		 // don't have right or left node is red
			//red node we judge left and right
		}
	//	System.out.println("root.val = "+root.val); // black node we judge left subtree and right subtree
			return Pro4(root.left) && Pro4(root.right);

	}
	
	
	/* get  from the node to leaf node will go through how many black node  */
	public static int getHeight(TreeNode root ) {
		if(root == null) 		
			return 0 ;
	//	System.out.println("getHeight of"+root.val);
		int leftHeight = getHeight(root.left);
		int rightHeight = getHeight(root.right);
	//	System.out.println("rootheight left right  = "+root.val+leftHeight+rightHeight);
		if(root.val > 0 )  //if root is black node
			return Math.max(leftHeight,rightHeight) +1;
		else 
			return Math.max(leftHeight,rightHeight);
	}
	
	/* judge property 5, whether or not any node go to leaf node through same number black node */
	public static Boolean Pro5(TreeNode root ) {
	//	System.out.println("judge property 5  begin");
		if(root == null) 	
			return true;
		if( getHeight(root.left) == getHeight(root.right) ) {
//			System.out.println("this node is correct ,judge his subtree ");
			return Pro5(root.left) && Pro5(root.right);
		}
		else 	
//			System.out.println("pro5 is false ");
		return false;
	}
	
	/*  judge print a Yes or no*/
	
	public static void judge(TreeNode root ) {
		if(root == null) {
			System.out.println("No");
		}
		if(root.val < 0 ) {
			System.out.println("No");
			// property 2 ,root is black,value >0
		}
		else {
			//property 4
			if(Pro4(root) && Pro5(root)) {
				System.out.println("Yes");
			}
			else {
				System.out.println("No");
			}
		}
	}
}
