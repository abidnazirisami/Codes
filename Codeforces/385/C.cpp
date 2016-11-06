#include <bits/stdc++.h>
using namespace std;
#define MX 10000010
vector <int> prim;
int ara[MX];
int cumul[MX];
int okay[MX];
void sieve () {
    int sqr = sqrt(MX);
    ara[0] = ara[1] = 1;
    for (int i=2; i*2<MX; i++) ara[i*2] = 1;
    prim.push_back(2);
    for (int i=3; i<=sqr; i++) {
        if (!ara[i]) {
            prim.push_back(i);
            for (int j=2; j*i<MX; j++) ara[i*j] = 1;
        }
    }
}
void primefacto (int n) {
    int cur = 0;
    int sz = prim.size();
    while (cur < sz && n > 1) {
        if(cur < sz && n%prim[cur] == 0) {
            okay[prim[cur]]++;
            while (n%prim[cur] == 0) {
                n/=prim[cur];
            }
        }
        cur++;
    }
    if (n>1) okay[n]++;
}
void cumulative () {
    int cur = 0;
    for (int i=0; i<MX; i++) {
        cur += okay[i];
        cumul[i] = cur;
    }
}
int query (int n, int m) {
    return cumul[m]-cumul[n-1];
}
int main () {
    sieve();
    int n, m;
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        scanf("%d", &m);
        primefacto(m);
    }
    cumulative();
    scanf("%d", &m);
    int a, b;
    for (int i=0; i<m; i++) {
        scanf("%d %d", &a, &b);
        if (a>MX) a=MX-1;
        if (b>MX) b =MX-1;
        printf("%d\n", query(a, b));
    }
    return 0;
}
