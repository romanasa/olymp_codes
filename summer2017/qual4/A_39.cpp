#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
typedef long long ll;
 
using namespace std;
 
const int dd = (int)2e5 + 1;
const int mod = (int)1e9 + 7;
 
int c[dd], used[dd];
vector<vector<int> > E, G;
 
int mul(int a, int b) {
    return 1ll * a * b % mod;
}
 
int add(int a, int b) {
    a += b;
    return a >= mod ? a - mod : a;
}
 
int calc(int v, int pr) {
    int cur = 1;
    for (int to : E[v]) if (to != pr) {
        cur = mul(cur, calc(to, v) + 1);
    }
    return cur;
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    E.resize(n);
    G.resize(n);
 
    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
    }
 
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        G[a - 1].push_back(b - 1);
        G[b - 1].push_back(a - 1);
    }
 
    vector<int> P(n);
    for (int i = 0; i < n; i++) P[i] = i;
    sort(P.begin(), P.end(), [](int a, int b) { return c[a] < c[b]; });
 
    int ans = 0;
    for (int v : P) {
        int cur = 1;
        for (int to : G[v]) if (used[to]) {
            cur = mul(cur, calc(to, v) + 1);
            E[v].push_back(to);
            E[to].push_back(v);
        }
        //err("v = %d, cur = %d\n", v, cur);
        ans = add(ans, mul(cur, c[v]));
        used[v] = 1;
    }
    printf("%d\n", ans);
 
    return 0;
}