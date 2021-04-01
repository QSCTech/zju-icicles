//
// Created by 12638 on 2021/3/11.
//
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <windows.h>
#include"Polynomial.h"
using namespace std;


List readBigdata(){
    List s = nullptr,temp,L;
    L = (struct Node*)malloc(sizeof(struct Node));
    temp = L;
    int n = 2000;// big data test, could also in linux,time  /a.out to test time used
    for(int i = 0 ;i < n ;i++){
        s = (struct Node *)malloc(sizeof(struct Node));
        s->coef = i ; s->exp = i;
        L->next = s;
        L = s ;
    }
    L->next = nullptr;
    return temp;
}

// test zero polynomial process
List zero(){
    List L,s;
    s = (struct Node *)malloc(sizeof(struct Node));
    L = (struct Node*)malloc(sizeof(struct Node));
    L->coef = 0 ;
    L->exp = 0;
    L->next = nullptr;
    s->next = L;
    return s ;
}
List sampa1(){
    List L,s,s2;
    s = (struct Node *)malloc(sizeof(struct Node));
    L = (struct Node*)malloc(sizeof(struct Node));
    L->coef = 2 ;
    L->exp = 2;
    s2 = (struct Node*)malloc(sizeof(struct Node));
    s2->coef = -2;
    s2->exp  = 1 ;
    s->next = L;
    L->next = s2;
    s2->next = nullptr;
    return s ;
}
List sampa2(){
    List L,s,s2;
    s = (struct Node *)malloc(sizeof(struct Node));
    L = (struct Node*)malloc(sizeof(struct Node));
    L->coef = 2 ;
    L->exp = 2;
    s2 = (struct Node*)malloc(sizeof(struct Node));
    s2->coef = 2;
    s2->exp  = 1 ;
    s->next = L;
    L->next = s2;
    s2->next = NULL;
    return s ;
}
List sampB1(){
    List L,s,s2;
    s = (struct Node *)malloc(sizeof(struct Node));
    L = (struct Node*)malloc(sizeof(struct Node));
    L->coef = 3 ;
    L->exp = 3 ;
    s2 = (struct Node*)malloc(sizeof(struct Node));
    s2->coef = 0 ;
    s2->exp  = 2 ;
    s->next = L;
    L->next = s2;
    s2->next = NULL;
    return s ;
}
List sampB2(){
    List L,s,s2;
    s = (struct Node *)malloc(sizeof(struct Node));
    L = (struct Node*)malloc(sizeof(struct Node));
    L->coef = 0 ;
    L->exp = 3;
    s2 = (struct Node*)malloc(sizeof(struct Node));
    s2->coef = 0;
    s2->exp  = 2 ;
    s->next = L;
    L->next = s2;
    s2->next = NULL;
    return s ;
}

List sampC1(){
    List L,s,s2,s3,s4;
    s = (struct Node *)malloc(sizeof(struct Node));
    L = (struct Node*)malloc(sizeof(struct Node));
    L->coef = 3 ;
    L->exp = 4;
    s2 = (struct Node*)malloc(sizeof(struct Node));
    s2->coef = -5;
    s2->exp  = 2 ;
    s3 = (struct Node*)malloc(sizeof(struct Node));
    s3->coef = 6;
    s3->exp  = 1 ;
    s4 = (struct Node*)malloc(sizeof(struct Node));
    s4->coef = -2;
    s4->exp  = 0 ;
    s->next = L;
    L->next = s2;
    s2->next = s3;
    s3->next = s4;
    s4->next = nullptr;
    return s ;
}
List sampC2(){
    List L,s,s2,s3;
    s = (struct Node *)malloc(sizeof(struct Node));
    L = (struct Node*)malloc(sizeof(struct Node));
    L->coef = 5 ;
    L->exp = 20;
    s2 = (struct Node*)malloc(sizeof(struct Node));
    s2->coef = -7;
    s2->exp  = 4 ;
    s3 = (struct Node*)malloc(sizeof(struct Node));
    s3->coef = 3;
    s3->exp  = 1 ;
    s->next = L;
    L->next = s2;
    s2->next = s3;
    s3->next = nullptr;
    return s ;
}

void print(List L){
    if(L->next!=NULL){
        L = L->next;
        while(L){
            if(L->next)
                cout<<L->coef<<" "<<L->exp<<" ";
            else
                cout<<L->coef<<" "<<L->exp<<endl;
            L = L->next;
        }
    }
    else
        cout<<0<<" "<<0<<endl;
}
void judgeZero(List L){
    if(L->next!=nullptr){
        L = L->next;
        assert(L->coef ==  1 );
        assert(L->exp == 0 );
    }
}

void judge3(List L){
    if(L->next != nullptr){
        L = L->next;
        assert(L->coef ==  0 );
        L =  L->next;
        assert(L->coef ==  0 );
    }
}


List getSum(List L1,List L2){
    List L,temp = nullptr,s = nullptr;
    L = (struct Node *)malloc(sizeof(struct Node));
    temp = L;
    while(L1->next && L2->next){//a，b都不为空的时候循环
        if(L1->next->exp > L2->next->exp){ //第一种，如果a的指数大于b直接添加a
            s = (struct Node *)malloc(sizeof(struct Node));
            s->coef = L1->next->coef;
            s->exp = L1->next->exp;
            L->next = s;
            L = s;
            L1 = L1->next; //移动到下一个节点
        }
        else if(L1->next->exp < L2->next->exp){
            s = (struct Node *)malloc(sizeof(struct Node));
            s->coef = L2->next->coef;
            s->exp = L2->next->exp;
            L->next = s;
            L = s;
            L2 = L2->next;
        }
        else{ // 指数相同
            if(L2->next->coef + L1->next->coef != 0) {
                s = (struct Node *) malloc(sizeof(struct Node));
                s->coef = L2->next->coef + L1->next->coef;
                s->exp = L2->next->exp;
                L->next = s;
                L = s;
            }//不管，他们的和是不是 0，我们都要，将L1,L2后移一个单位。
            L1 = L1->next;
            L2 = L2->next;
        }
    }
    // 最后有一个先没, 后面的接上即可.
    if (!L1->next) {
        L->next = L2->next;
    } else {
        L->next = L1->next;
    }
    return temp;
}


List getMuti(List L1,List L2){
    /*
    我们采用逐项插入
    1，先拿出L2的第一项，让它与L1的每一项相乘。从而得到 L。
    2，拿出L2的第二项，让它与L1的每一项相乘，然后每乘一项，就将其插入到 L中。
    3，依次重复上面的步骤，最终得到L。将其打印出来。
    */
    List L,temp = NULL,s = NULL;
    L = (struct Node *)malloc(sizeof(struct Node));
    temp = L;
    List La = L1;

    //取出L2的第一项，让它与L1的每一项相乘。从而得到 L。
    while(La->next){
        s = (struct Node *)malloc(sizeof(struct Node));
        s->coef = La->next->coef * L2->next->coef;
        s->exp = La->next->exp + L2->next->exp;
        L->next=s;
        L = s;
        La = La->next;
    }
    L->next = NULL;
    L = temp;
    List Lb = L2->next;
    bool flag = true;
    /*
    在这里说明一下 flag 在这里的作用：
    用于标记，在下面的程序中，是否进行了，  if( > ) 和 if( == )里面的操作，
    若进行了，则flag就变为 false，则不用进行， while(.....){.....},结束后的第一条语句，
    这条语句的含义是，在L中没有找到，这个 待插入项 的位置，所以将其置于l的尾部。
    */
    while(Lb && Lb->next){
        La = L1;
        while(La->next){
            s = (struct Node *)malloc(sizeof(struct Node));
            s->coef = La->next->coef * Lb->next->coef;
            s->exp = La->next->exp + Lb->next->exp;
            //得到的s插入L中.
            while(L->next){
                if(s->exp > L->next->exp){
                    List val = L->next;
                    L->next = s;
                    s->next = val;
                    flag = false;
                    break;
                }
                else if(s->exp == L->next->exp){
                    if(s->coef + L->next->coef == 0){
                        List val = L->next->next;
                        L->next = val;////如果相等，非0时，系数相加,为0时,删除掉该节点
                    }
                    else
                        L->next->coef += s->coef;
                    flag = false;
                    break;
                }
                L = L->next;
            }
            // 如果没有插入到L中,那就放在最后
            if(flag){
                L->next = s;
                s->next = nullptr;
            }
            L = temp;
            La = La->next;
            flag  = true;
        }
        Lb = Lb->next;
    }
    return temp;
}

int main(){
    List L1,L2,L=nullptr;
    DWORD star_time = GetTickCount();
//     L1 = readBigdata();
//     L2 = readBigdata();
    // L1 = zero();
    // L2 = zero();
//    L1 = sampa1();
//    L2 = sampa2();
//    L1 = sampB1();
//    L2 = sampB2();
    L1 = sampC1();
   L2 = sampC2();
    L = getMuti(L1,L2);
    print(L);
  //  judge3(L);
//    judgeZero(L);
    L = getSum(L1,L2);
    print(L);
    DWORD end_time = GetTickCount();
    cout << "这个程序运行时间为：" << (end_time - star_time) << "ms." << endl;
    return 0;
}
