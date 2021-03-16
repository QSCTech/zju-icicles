///* Author: Lin Juyi;  ID: 3180103721;  No.02 */
// Created by 12638 on 2020/12/14.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int Set[1020];
int cmp1(int a, int b){
    return a > b;
} // for non increasing sort
void init(int n) {
    int i ;
    for(i = 1; i <= n ;i++){
        Set[i] = -1 ;   // 一开始，size都是1 ，没有根、
    }
}

int Find(int x){
    if(Set[x] <= -1){
        return x; // if this is a root
    }
    Set[x] = Find(Set[x]);// recursion for path compassion
    return Set[x] ;
}

void Union(int x, int y){
    int root1;
    root1 = Find(x);
    if(root1 == y ) {
        return;// in the identical cluster
    }
    if(Set[root1] > Set[y]){   // -2> -3 ,merge -2 cluster into -3
        Set[y] = Set[root1] + Set[y];
        Set[root1] = y; // pointer at y
    }
    else{
        Set[root1] = Set[root1] + Set[y];
        Set[y] = root1;// pointer at root1
    }
}

int main(){
    int N,i,Ki,temHobby,j;
    char comma;
    int course[1010] = { 0 };
    init(1010);
    cin >> N;
    for(i = 1; i <= N;i++){ // we should start at serial 1 not 0
        cin >> Ki;
        cin >> comma;
        for(j = 0 ;j < Ki;j++){
            cin >> temHobby;  // 记录喜欢course[t]当前人的编号
            if(course[temHobby] == 0 ){
                //Don't have any people like this
                course[temHobby] = i ; // i is the serial number of the man
            }
            else{
                Union(i, Find(course[temHobby]) ); //
                // union this person into cluster. for example ,we save (human 1) h1  like c2 in course[]
                // then we  union h1 and h2 in the set[]
                // and then if h3 like c2, course[temHobby] = h1
                // we union h3 and the root of h1 in the set[]
            }
        }
    }
    int total = 0,k = 0;
    vector<int> vectorout;
    for( i = 1 ; i <= N;i++){
        if(Set[i] <= -1){
            total ++;
            vectorout.insert(vectorout.end(),-Set[i]);
        }
    }
    cout << total <<endl;
    sort(vectorout.begin(),vectorout.end(),cmp1);
    printf("%d",vectorout[k++]) ;
    while(vectorout[k]){
        printf(" ");
        printf("%d",vectorout[k++]) ;
    }
}
