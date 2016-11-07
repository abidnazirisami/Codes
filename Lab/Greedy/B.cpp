/*
You are given a N items. Each item has a weight and price associated with it. You need to fill up a knapsack of capacity C. Your target is to fill the knapsack in such a way that you can have maximum profit. You don't need to fill the knapsack to the full. You can take fraction of an item. The price will be adjusted in ratio.

Input

First line: T ( 0 < T < 100), number of test cases. Next T lines each: N C (0 < N < 30, 0 <= C <= 30,000). Next Line, N integers, Wi, (0 < Wi < 1000), weight of the ith element. Next Line, N integers, Pi, (0 < Pi < 1000), price of the ith element.

Output

Output maximum profit upto two decimal places. you can take in the knapsack. See sample for clarification

Sample
Input	Output
1
5 10
2 5 3 10 1
2 7 1 10 2	13.00
*/

#include <bits/stdc++.h>
using namespace std;
#define INF -1
typedef struct nod {
    int w, c;
    double r;
}  node;
node ara[40];
int n, m;
bool cmp (node a, node b) {
    return a.r < b.r;
}
int main () {
    int T;
    scanf("%d", &T);
    for (int cs=1; cs<=T; cs++) {
        scanf("%d %d", &n, &m);
        for (int i=0; i<n; i++) scanf("%d", &ara[i].w);
        for (int i=0; i<n; i++) scanf("%d", &ara[i].c);
        for (int i=0; i<n; i++) ara[i].r = ((double)ara[i].c * 1.0) / double (ara[i].w);
        sort (ara, ara+n, cmp);
        double ans = 0;
        for (int i=n-1; i>=0; i--) {
            if (m==0) break;
            if (ara[i].w <= m) {
                ans += ara[i].c;
                m -= ara[i].w;
            }
            else {
                ans = ans + m*ara[i].r;
                m=0;
            }
        }
        printf("%.2lf\n", ans);
    }
    return 0;
}
