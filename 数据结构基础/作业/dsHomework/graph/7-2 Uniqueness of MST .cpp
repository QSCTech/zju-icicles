//
// Created by 12638 on 2020/12/7.
/*
题目大意：给出一个无向图，判断是否能生成最小生成树，
 如果可以生成最小生成树，那么判断生成的最小生成树是否唯一，如果不能生成最小生成树，求有几个连通分量。
//解题思路：Kruskal最小生成树算法。首先关于最小生成树是否唯一，存在不唯一的情况即为有两个（及以上）权值相同的边，
 且最终的最小生成树只需要使用其中任意一个边，此时最小生成树不唯一。
 所以可以想到对于权值相同的一串边，先判断当前是否能作为最小生成树的边（用isTreeEdge标记），
然后将能够作为最小生成树的边依次加入已经生成的最小树中，若出现某个边由于前面相同权值边的影响而不能加入最小树，此时说明最小生成树不唯一。
 而对于连通分量的求解，在求最小生成树的时候，每次加入一个新边的时候记一下数，最后用顶点数-该数即为连通分量的值。
//
*/
/*
typedef struct{
    int u, v, w;
    bool isTreeEdge = false;
}Edge;
vector<Edge>edges;
int n, m;
typedef struct ufset * UFset;
typedef struct ufset{
    int * father;
}UFS;
//union and find
UFset UFinit(int size){
    int e ;
    UFset U = (UFset)(malloc(sizeof *U));
    U->father = (int *)(malloc((size + 1) * sizeof(int)));
    for(e = 1 ; e<= size;e++){
        U->father[e] = 0 ;
    }
    return U;
}
int UFunion(int i, int j,UFset U){
    U->father[j] = i ;
    return i ;
}
int UFfind(int x,UFset U){
    if(x == U->father[x])
        return x; // 如果她是树顶,就直接返回
    int i,j = x ;
    j = UFfind(U->father[x],U); // find the root
    while(j!= x){
        i = U->father[x];  // save the father of x
        U->father[x] = j; // x father point root
        x = i ; // next
    }
    //int a = UFfind(U->father[x],U); // 找到树顶
    //U->father[x] = a;   //然后把x的位置指向树顶. 没有路径压缩
    return j;
}
 int main() {
  cin >> n >> m;
    edges.resize(m);
    UFset U;
    U = UFinit(m);
    int i ;
    for (i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;// input all edgesmmm
    }
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) { return a.w < b.w; });
    //边排序,,,.
    iota(U->father, U->father + n + 1, 0);//iota函数对一个范围数据进行赋值：
 //   cout << "init finished"<<endl;
    //init 集合
    //解题思路：Kruskal最小生成树算法。首先关于最小生成树是否唯一，存在不唯一的情况即为有两个（及以上）权值相同的边，
    // 且最终的最小生成树只需要使用其中任意一个边，此时最小生成树不唯一。
    // 所以可以想到对于权值相同的一串边，先判断当前是否能作为最小生成树的边（用isTreeEdge标记），
    //然后将能够作为最小生成树的边依次加入已经生成的最小树中，若出现某个边由于前面相同权值边的影响而不能加入最小树，此时说明最小生成树不唯一。
    // 而对于连通分量的求解，在求最小生成树的时候，每次加入一个新边的时候记一下数，最后用顶点数-该数即为连通分量的值。
    int sum = 0, num = 0, j = 0;
    bool flag = true;
    for (int i = 0; i < edges.size(); i = j) { // traversal all edges
        for (j = i; j < edges.size() && edges[j].w == edges[i].w; ++j) { //如果权重相同
      //      cout << "try1"<<endl;
            if ( UFfind(edges[j].u,U) != UFfind(edges[j].v,U) ) {
                edges[j].isTreeEdge = true;// if in same set
            }
              // could be a edge to add in Tree
           // cout << "istree"<<endl; //
        }
       // cout << "find edge to add in Tree "<<endl;
        for (int k = i; k < j; ++k) {
            int ua = UFfind(edges[k].u,U), ub = UFfind(edges[k].v,U);
            if (ua != ub) {
                sum += edges[k].w;//total weight
                UFunion(ua,ub,U);//father[ua] = ub;// 合并连通分支
                ++num;
            } else {
                if (edges[k].isTreeEdge)
                    flag = false;
            }
       //     cout << "join  edge "<<endl;
        }
    }
    if (num == n - 1) {
        cout << sum << endl;
        cout << (flag ? "Yes" : "No");
    } else {
    cout << "No MST" << endl;
    cout << n - num;
    }
}
*/
