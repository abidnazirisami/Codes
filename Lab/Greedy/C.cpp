/*
You are given a N coins such that each of them will be a multiple of the smaller coins. You need to give change to amount C. Use minimum number of coins.

Input

First line: T ( 0 < T < 100), number of test cases. Next T lines each: N C (0 < N < 30, 0 <= C <= 10^9). Next Line, N integers, Ai, (Ai will be less than 2^64), value of the ith coin.

Output

Output minimum no of coin required. you can use a coin multiple times. If not possible output “Impossible”. See sample for clarification

Sample
Input	Output
1
4 10
1 3 6 12	3
*/

#include <bits/stdc++.h>
using namespace std;
long long n, m, ara[100];
int main () {
    int T;
    scanf("%d", &T);
    for (int cs=1; cs<=T; cs++) {
        cin >> n >> m;
        for (int i=0; i<n; i++) cin >> ara[i];
        sort(ara, ara+n);
        long long int cnt = 0;
        for (int i=n-1; i>=0; i--) {
            if (m==0 || ara[i]<=0) break;
            if (m/ara[i] > 0) {
                cnt = cnt + m/ara[i];
                m = m%ara[i];
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}
