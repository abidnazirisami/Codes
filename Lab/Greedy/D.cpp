/*
You are given a N intervals for N tasks. Find maximum no of non intersecting tasks you can finish.

Input

First line: T ( 0 < T < 100), number of test cases. Next T lines each: N (0 < N < 1000). Next line, N integers, Li, (Li will be less than 1000000000), starting time of the ith interval. Next line, N integers, Ri, (Li <=Ri and Ri will be less than 1000000000), endin time of the ith interval. You can start a taks immediately after a task finishes.

Output

Output maximum no of tasks that can be finished. See sample for clarification

Sample
Input	Output
1
4
1 3 6 7
4 10 7 10	3
*/
#include <bits/stdc++.h>
using namespace std;
typedef struct nod {
    int s, f;
} node;
node ara[1010];
bool cmp(node a, node b) {
    if (a.f == b.f) return a.s < b.s;
    else return a.f < b.f;
}
int main () {
    int T, n;
    scanf("%d", &T);
    for (int cs=1; cs<=T; cs++) {
        scanf("%d", &n);
        for (int i=0; i<n; i++) scanf("%d", &ara[i].s);
        for (int i=0; i<n; i++) scanf("%d", &ara[i].f);
        sort (ara, ara+n, cmp);
        int cnt = 0, taken = -1;
        for (int i=0; i<n; i++) {
            if (ara[i].s >= taken) {
                cnt++;
                taken = ara[i].f;
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}
