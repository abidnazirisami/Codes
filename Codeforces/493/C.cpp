#include <bits/stdc++.h>
#define int long long
using namespace std;
map <int, int> a1;
map <int, int> a2;
set <int> S;
main () {
    int n, m, a, x1, x2;
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> a;
        S.insert(a);
        a1[a]++;
    }
    cin >> m;
    for (int i=0; i<m; i++) {
        cin >> a;
        S.insert(a);
        a2[a]++;
    }
    int a11, a22, ans;
    a11 = n*3;
    a22 = m*3;
    ans = a11-a22;
    x1 = a11;
    x2 = a22;
    set <int> :: iterator it;
    for (it = S.begin(); it != S.end(); it++) {
        a11 = a11 - a1[*it]*3 + a1[*it]*2;
        a22 = a22 - a2[*it]*3 + a2[*it]*2;
        if (a11-a22 > ans) {
            ans = a11-a22;
            x1 = a11;
            x2 = a22;
        }
    }
    cout << x1 << ":" << x2 << "\n";
    return 0;
}
