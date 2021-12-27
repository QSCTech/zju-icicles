////
//// Created by 12638 on 2021/1/1.
////可以使用拓扑排序来解这道题。基本思路如下：将输入保存在散列表后，
//// 遍历每个元素，如果元素刚好在它对应余数的位置上，则入度为0，可直接输出；
//// 否则，从余数位置出发，用线性探测法到达该位置，对于经过的所有的非空元素位置，生成一条到该元素位置的边，并将该位置入度加1；
//// 拓扑排序时，可以采用优先队列，优先输出数值较小的元素
//#include<iostream>
//#include<queue>
//using namespace std;
//vector<int> G[1000]; // 连接表,有1000个vector.
//int degree[1000]={0}; // 入度
//int a[1000];
//struct myCompare{ // 为优先队列自定义操作
//    bool operator()(int m,int n){
//        return a[m]>a[n];
//    }
//};
//// 拓扑排序时，可以采用优先队列，优先输出数值较小的元素
//void tSort();
//void tSort(int N) { // 拓扑排序 从一个顶点出发遍历一遍图.
//    priority_queue<int,vector<int>,myCompare> q;// 标准stl可以传入struct定义比较, 自己定义的类可以直接在里面定义方法.
//    for(int i = 0 ; i <N; i++){
//        if (degree[i] == 0 && a[i] >= 0 ){
//            q.push(i);
//        }
//    }
//    bool firstOutput = false;
//    while ( !q.empty() ){
//        (firstOutput ? cout << ' ' : cout) << a[q.top()];
//        firstOutput  = true;
//        int t = q.top();
//        q.pop();
//        for (int & i : G[t]) { // 把和他相连的都处理一遍 int i不会回带参数，而int &i可以回带参数 int i 可赋予常量，而int & i 不能 int &i 相当于别名，而int i 只是拷贝
//                degree[i]--;
//            if (!degree[i]){
//                q.push(i);
//            }
//        }
//    }//q 记录下表.没有入度, 那就直接输出.如果有, 那就插入, 排序.
//        // 输出q的top,然后q pop,把连接表连接的 入度--,如果为0 了,再push回去.
//}
//
//int main(){
//    int N;
//    cin >> N;
//    for(int i = 0;i < N;i++){ // 建图
//        cin >> a[i];
//        //有偏移的特殊处理.
//        if (a[i] % N != i && a[i] >= 0) { // >=0 shows 非空,  不能用-1因为他没说是-1只说是负数. 空的和没有偏移的直接输出.
//            int tmp;
//            tmp = a[i] % N;
//            while (tmp != i ){
//                degree[i]++;
//                G[tmp].push_back(i);//连接起来.
//                tmp = (tmp+1)%N;
//            }
//        }// 遍历每个元素，如果元素刚好在它对应余数的位置上，则入度为0，可直接输出；
//    }
//    tSort(N);
//    return 0;
//}
