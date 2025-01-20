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
    float Data[Max_Expr];   // �洢Ԫ�ص�����
    int top;       //ջ��ָ��
}Stack;
typedef Stack *StacktoPtr;

int Push(StacktoPtr S, float x)// topָ����ߵ��Ǹ� 
{ 
	printf("input push = %f\n",x); 
	printf("top  =%d\n",S->top); 
    S->Data[++S->top] = x;
    printf("top data =%f\n",S->Data[S->top]); 
    // ����top
    return S->top;
}

float Pop(StacktoPtr S) //
{ 
	if(S->top == -1){
		return Infinity;
	}
    return S->Data[S->top--];
}
//�����������,����һ�������¼�������,ֱ��������һ���ո�,�Ͱ�������Ķ���ת��Ϊ����,�����������.
//������� - ��+ , �����һ��������,�Ǿ������¼,�����һ���ǿո�,�Ǿ�pop����,���������ȥ. 
//�������*��/,�Ǿ�pop����,���top<1,�ǾͲ���,����error,���/0,��Ҳerror
//i++��������,ֱ�� '\0'
//��� topΪ0, �Ǿ��������, ����ʹ���. 
ElementType EvalPostfix( char *expr ){
	Stack S;
	S.top = -1;
   int i = 0,j = 0;
   float num  = 0,res =0;
   char b[100000];
   float op1,op2;
   while(expr[i] == ' ') {   
	   i++;
   }  //�ų��ո� 
   while(expr[i] != '\0'){
	  	if(  (expr[i] >='0' &&expr[i] <='9')  || expr[i] == '.'){
		  	b[j++] = expr[i];
		  	if(expr[i+1] == '\0' || expr[i+1] == ' '){
		  		b[j] = '\0'; //��b��ֹʹ��atof���� 
				num = atof(b);
		  		Push(&S , num);
		  		j = 0 ;
			}
	  	}
	  	else if(expr[i] == '-' || expr[i] == '+'){
		  	if(expr[i+1] >='0' &&expr[i+1] <='9' ){
		  		b[j++] = expr[i] ;  	//���� 
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
		//ʲô������ 
		} 
		else		return Infinity;
		i++; 
	}
	if(S.top == 0){
		return S.Data[0];
	}
	else return Infinity; 
	  
	  
}
   
//���¶���Max_Expr������30�ַ�,�𰸴��� ������, �ǳ���30�ַ�����erroô?��sizeof p����4,strlen��û��string�� 

//ֻ��1�������� , ������, ����3 ,����3 �ѵ�������?�ѵ�����error??  
   
   
   

            
