package dshomewrok;
import java.util.*;
//首先 , 从小到大排序,就是这个树的中序遍历
//递归法, 首先如果到叶了,就return, 否则先往左一直过去, level[i++] root*2+1), 左边递归完了,然后中间 = in[root], 然后右边递归判断
//
public class CompletBinarySearchTree {
	static int count = 0,root =0;
	static int[] level = new int[1010];//动态数组的标准分配
	public static  void main(String[] args) {
		int i=0,j = 0, k = 0,n = 0;
	    Scanner sc = new Scanner(System.in); 
	    k = sc.nextInt();   // k is number of the  tree's node
	    int[] arr = new int[k];//动态数组的标准分配
	    for(j = 0;j < k;j++) {
	    		 arr[j] = sc.nextInt();
		}
	    Arrays.sort(arr);//得到树的中序遍历
	    System.out.print(arr[0]);
	 //   System.out.println(Arrays.toString(arr2));
	    Build(arr,root);
	    System.out.print(level[0]);
	    for(i = 1;i<k;i++) 	    	
	    	System.out.print(" "+level[i]);// no extra space, you could ,first print [0], and then print "space"+[i]
	    sc.close();
	}
	
	public  static void Build(int[] arr, int root) {
		if(root >= arr.length) return;  // arrive leaf
		Build(arr,root*2+1);
	    level[root]	= arr[count++];
 	    Build(arr,root*2+2);
	}
}
/*Arrays类中的sort()使用的是“经过调优的快速排序法”;
(2)比如int[]，double[]，char[]等基数据类型的数组，Arrays类之只是提供了默认的升序排列，没有提供相应的降序排列方法。
(3)要对基础类型的数组进行降序排序，需要将这些数组转化为对应的封装类数组，如Integer[]，Double[]，Character[]等，对这些类数组进行排序。(其实还不如先进行升序排序，自己在转为将序)。
*/