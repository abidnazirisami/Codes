/*
Once upon a time there lived a greedy landlord in a not far far away country. The landlord used to
employ armed enforcers to ensure tax collection from his subjects. All his subjects were farmers and
they depended solely on their crops to pay tax. In any single year, an individual farmer had crops in
his  eld during a single continuous time interval. During this interval, an enforcer from the landlord
was present in the farmer's  eld so that he could make sure to take away most of the produced crops
to the landlord's burn. An enforcer could take care of at most one farmer at a time.
Now, in a glorious lazy morning, the landlord realized that a lot of his subjects were having in-
tersecting production intervals. As he was determined to take the lion's share of crops from all the
farmers, he sat down to determine the minimum number of enforcers he needed to ensure that no farmer
remained unguarded while having crops in his  eld.
Oh your royal greediness! Don't you realize he who is greedy is always in want?
Input
There will be multiple test cases in the input  le. A test case starts with an integer
N
(0

N

1000),
denoting the number of farmers. Each of the following
N
lines contains 2 integers
S
&
E
(0

S

E

31536000), the starting & ending time respectively of the production interval of a farmer. Note
that time is given in seconds from the start of the year.
The end of input will be denoted by a case with
N
=

*/

#include <bits/stdc++.h>
using namespace std;
typedef struct nod {
    int s, flag;
} node;
node ara[2010];
bool cmp(node a, node b) {
    if (a.s == b.s) return a.flag < b.flag;
    return a.s < b.s;
}
int main () {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int T=1, n;
    while (scanf("%d", &n) != EOF) {
        if (n==-1) break;
        for (int i=0; i<2*n; i+=2) {
            scanf("%d %d", &ara[i].s, &ara[i+1].s);
            ara[i].flag = 0;
            ara[i+1].flag = 1;
        }
        sort (ara, ara+2*n, cmp);
        int x = 0;
        int cnt = 0;
        for (int i=0; i<2*n; i++) {
            if (ara[i].flag == 0) cnt++;
            else cnt--;
            x = max(cnt, x);
        }
        printf("Case %d: %d\n", T++, x);
    }
    return 0;
}
