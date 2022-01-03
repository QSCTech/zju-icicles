#include <stdio.h>
#include <stdlib.h>

typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 5   /* max size of expression */

ElementType EvalPostfix( char *expr );

int main()
{
    ElementType v;
    char expr[Max_Expr];
    gets(expr);
    v = EvalPostfix( expr );
    if ( v < Infinity )
        printf("%f\n", v);
    else
        printf("ERROR\n");
    return 0;
}

typedef struct
{
    float Data[Max_Expr];   // 存储元素的数组
    int top;       //栈顶指针
}Stack;
typedef Stack *StacktoPtr;

int Push(StacktoPtr S, float x)// top指向最高的那个 
{ 
	printf("input push = %f\n",x); 
	printf("top  =%d\n",S->top); 
    S->Data[++S->top] = x;
    printf("top data =%f\n",S->Data[S->top]); 
    // 返回top
    return S->top;
}

float Pop(StacktoPtr S) //
{ 
	if(S->top == -1){
		return Infinity;
	}
    return S->Data[S->top--];
}
//如果遇到数字,用另一个数组记录这个数字,直到遇到下一个空格,就把数组里的东西转化为数字,并且清空数组.
//如果遇到 - 或+ , 如果下一个是数字,那就数组记录,如果下一个是空格,那就pop两个,加起来或减去. 
//如果遇到*或/,那就pop两个,如果top<1,那就不够,返回error,如果/0,那也error
//i++继续遍历,直到 '\0'
//如果 top为0, 那就输出数字, 否则就错误. 
ElementType EvalPostfix( char *expr ){
	Stack S;
	S.top = -1;
   int i = 0,j = 0;
   float num  = 0,res =0;
   char b[100000];
   float op1,op2;
   while(expr[i] == ' ') {   
	   i++;
   }  //排除空格 
   while(expr[i] != '\0'){
	  	if(  (expr[i] >='0' &&expr[i] <='9')  || expr[i] == '.'){
		  	b[j++] = expr[i];
		  	if(expr[i+1] == '\0' || expr[i+1] == ' '){
		  		b[j] = '\0'; //把b截止使用atof函数 
				num = atof(b);
		  		Push(&S , num);
		  		j = 0 ;
			}
	  	}
	  	else if(expr[i] == '-' || expr[i] == '+'){
		  	if(expr[i+1] >='0' &&expr[i+1] <='9' ){
		  		b[j++] = expr[i] ;  	//负数 
		  		printf("b[%d] =%c\n",j,expr[i]); 
			} 
			else if(expr[i+1] == '\0' || expr[i+1] == ' '){
				op1 = Pop(&S);
				op2 = Pop(&S);
				if(op1 == Infinity || op2 ==Infinity){
					return Infinity;
				}
				else{
					if(expr[i] == '-'){
						res = op2-op1;
					}
					if(expr[i] == '+'){
						res = op1+op2;
					}
					Push(&S,res);
				}
			}
			else return Infinity;
	    }
		else if(expr[i] == '*' || expr[i] == '/'){
				op1 = Pop(&S);
				op2 = Pop(&S);
				if(op1 == Infinity || op2 ==Infinity){
					return Infinity;
				}
				else{
					if(expr[i] == '/'){
						if(op1 == 0) return Infinity; 
						res = op2/op1;
					}
					if(expr[i] == '*'){
						res = op1*op2;
					}
					Push(&S,res);
				}
		}
		else if(expr[i] == ' '){
		//什么都不做 
		} 
		else		return Infinity;
		i++; 
	}
	if(S.top == 0){
		return S.Data[0];
	}
	else return Infinity; 
	  
	  
}
   
//重新定义Max_Expr，超过30字符,答案错误 不明白, 是超过30字符返回erro么?用sizeof p都是4,strlen又没有string库 

//只有1个运算数 , 不明白, 输入3 ,返回3 难道不对吗?难道返回error??  
   
   
   

            
