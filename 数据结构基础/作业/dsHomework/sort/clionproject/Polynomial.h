//
// Created by 12638 on 2021/3/11.
//

#ifndef CLIONPROJECT_POLYNOMIAL_H
#define CLIONPROJECT_POLYNOMIAL_H

typedef struct Node{
    int coef;//绯绘暟
    int exp;//鎸囨暟
    struct Node *next;
} *List;



List read(List L);
void print(List L);
// gain the sum of two polynomial
List getSum(List L1,List L2);
// gain the multiplication of two polynomial
List getMuti(List L1,List L2);

List readBigdata(List L);
List zero();
List sampa1();// input  2 2 -2 1
List sampa2();//2 2 2 1
List sampC2();// input 5 20  -7 4  3 1
List sampC1();// input 3 4 -5 2  6 1  -2 0
List sampB1();// input 3 3 0 2
List sampB2();// input 0 3 0 2
void judgeZero(List L);
void judge3(List L);// test 3 3 0 2 和 0 3 0 2 相乘

#endif //CLINCHER_POLYNOMIAL_H
