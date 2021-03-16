package dsHomework;
import java.util.*;
public class PopSequence {
	// m 从0 到6,是序列的循环变量,  m ==7时,序列就结束了,m is 序列的index, v从1到7, 是入栈的元素
	// 如果 入栈的元素小于序列,那就入栈,直到大于序列.
	//如果爆栈,那就error, ,如果栈非空且peek = datam ,那就pop
	//如果栈顶大于序列,那就error.
		public static int StackCheck(int data[],int MaxSize) {
	        Stack <Integer> st = new Stack<Integer>(); //Integer 类型的栈
    	    int v = 1, m = 0,N = data.length ;
    	//    System.out.print(data.length);
    	    while(m < N) { 
    	    
    	    	while( v <= data[m] ) {   // v from 1 to 7
	    	    	st.push(v) ;
	    	//   	System.out.println("入栈的是"+v);
	    	    	v++; 
	    	    }//此时 v =data[0]+1
	    	//   System.out.print("   data[m] = "+data[m]);
	    	    if(st.size() > MaxSize) {
	    	    	return 0 ;
	    	    }
	    	 //   System.out.println("栈顶是"+st.peek());
	    	    if(  (!st.empty())&& st.peek() == data[m] ) {
	    	    st.pop();
	    	  //  System.out.print(" pop  success");
	    	    }
	    		if( !st.empty()  && st.peek() > data[m] ) {  // st.peek 放在后面否则会有emptystack异常. 
	 	    	    	return 0;
	 	    	}
	    	    m++;
    	    //	System.out.println("判断序列data["+m);
    	    }
    	    if(m == N) return 1;
    	    else return 0 ;	
		}
			
		
		public static void main(String[] args) {
		        int i = 0,j = 0,flag = 0,M = 0,N = 0,K = 0;
		        Scanner sc = new Scanner(System.in);
		        M = sc.nextInt();
		        N = sc.nextInt();
		        K = sc.nextInt();
		    // M (the maximum capacity of the stack), 
		        //N (the length of push sequence), and K (the number of pop sequences to be checked).
		    	for( i = 0;i < K;i++){  //K次读入序列
		    	    int data[] = new int[N]; /*开辟了一个长度为N的数组*/
		    	  //读入序列
		    	    for(j = 0;j < N; j++){
		    	    	data[j] = sc.nextInt(); 
		    	    }
		    	  //读入序列
		    	   flag = StackCheck(data,M);
		    //	   System.out.print("判断完了"+i);
		    	   if(flag == 1) {
		    		   System.out.println("YES");
		    	   }
		    	   else System.out.println("NO");
		    	} 
		    	    //print result and turn to next sequences   
		    	sc.close();
		}
		
}

	// 首先, 保存输入序列,第一个data和1不同,那1入栈,2,3,如果栈满了还是和第一个不同,那就error
	// 如果栈没满,stack[top]和第一个相同,那就出栈, 第二个和stack[top]相同,继续出栈,不相同,继续入栈,
	// 直到判断到第N个,出栈成功,那就right.中间栈满了或者top==-1了,那就error.

