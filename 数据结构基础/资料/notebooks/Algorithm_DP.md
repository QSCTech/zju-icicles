# DP

动态规划

最重要的是画出递归树,

n为1 或者2的时候往往特殊处理.

备忘录 : 

```cpp
int fib(int N){
    vector<int> dp(N+1, 0 );
    dp[1] = dp[2] = 1;// base case
    for(int i = 3;i <= N; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[N];
}
```





最优子结构

怎么符合最优子结构? 比如amout =11. amount =10的最少硬币数, 就+1 ,因为硬币数量没有限制, 子问题互相独立.