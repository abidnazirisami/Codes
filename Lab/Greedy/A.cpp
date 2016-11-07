/*
You are given a N items. Each item has a weight and price associated with it. You need to fill up a knapsack of capacity C. Your target is to fill the knapsack in such a way that you can take maximum number of elements. You don't need to fill the knapsack to the full.

Input

First line: T ( 0 < T < 100), number of test cases. Next T lines each: N C (0 < N < 30, 0 <= C <= 30,000). Next Line, N integers, Wi, (0 < Wi < 1000), weight of the ith element. Next Line, N integers, Pi, (0 < Pi < 1000), price of the ith element.

Output

Output maximum number of items you can take in the knapsack. See sample for clarification

Sample
Input	Output
1
5 10
2 5 3 10 1
2 3 1 30 1	3
*/
    
    #include <bits/stdc++.h>
    using namespace std;
    #define INF -1
    int cost[40];
    int weight[40];
    int dp[40][30010];
    int n, m;
    int func(int idx, int sum) {
        if (idx >= n) return 0;
        if (dp[idx][sum] != -1) return dp[idx][sum];
        if (sum + weight[idx] <= m) return dp[idx][sum] = max(func(idx+1, sum), 1 + func(idx+1, sum+weight[idx]));
        return dp[idx][sum] = func(idx+1, sum);
    }
    int main () {
        int T;
        scanf("%d", &T);
        for (int cs=1; cs<=T; cs++) {
            scanf("%d %d", &n, &m);
            memset(dp, -1, sizeof dp);
            for (int i=0; i<n; i++) scanf("%d", &weight[i]);
            for (int i=0; i<n; i++) scanf("%d", &cost[i]);
            printf("%d\n", func(0, 0));
        }
        return 0;
    }
