#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)3e5 + 7;
 
inline int readChar() {
    int c = getchar();
    while (c <= 32)
        c = getchar();
    return c;
}
 
inline int readInt() {
    int c = readChar();
    int res = 0;
    while ('0' <= c && c <= '9')
        res = res * 10 + c - '0', c = getchar();
    return res;
}
 
int col[dd];
int p[dd], level[dd];
 
int ans = 0;
const int mod = (int)1e9 + 7;
 
inline void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}
 
inline void sub(int &a, int b) {
    a -= b;
    if (a < 0) a += mod;
}
 
inline int get(ll x) {
    if (x >= mod) return x % mod;
    return x;
}
 
vector<vector<int> > E;
 
unordered_map<int, int> C, S, SQ;
vector<pair<int, pair<int, int> > > H;
 
int dfs(int v, int pr, int sz, int &center) {
    int cur = 1;
 
    for (int to : E[v]) {
        if (level[to] == -1 && to != pr) {
            cur += dfs(to, v, sz, center);
        }
    }
    if (center == -1 && (pr == -1 || cur * 2 >= sz))
        center = v;
    return cur;
}
 
void calc(int v, int pr, int d, int root, int k) {
    C[col[v]]++;
    add(S[col[v]], get(d));
    add(SQ[col[v]], get(1ll * d * d));
 
    //err("add v =%d, center = %d\n", v, root);
 
    if (k != -1) {
        H.push_back(make_pair(k, make_pair(v, d)));
    }
 
    for (int to : E[v]) {
        if (level[to] > level[root] && pr != to) {
            calc(to, v, d + 1, root, (k == -1 ? to : k));
        }
    }
}
 
void build(int v, int pr, int sz, int h) {
    int center = -1;
    dfs(v, -1, sz, center);
 
    p[center] = pr;
    level[center] = h;
 
    for (int to : E[center]) {
        if (level[to] == -1) {
            build(to, center, sz / 2, h + 1);
        }
    }
}
 
int main() {
    int n, m;
    n = readInt(), m = readInt();
 
    for (int i = 0; i < n; i++) {
        col[i] = readInt();
    }
 
    E.resize(n);
 
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        a = readInt(), b = readInt();
        E[a - 1].push_back(b - 1);
        E[b - 1].push_back(a - 1);
    }
 
    for (int v = 0; v < n; v++) {
        sort(E[v].begin(), E[v].end());
    }
 
    fill(level, level + n, -1);
    fill(p, p + n, -1);
 
    build(0, -1, n, 0);
 
 
 
 
    for (int v = 0; v < n; v++) {
 
        H.clear();
 
        calc(v, -1, 0, v, -1);
 
        int j = 0;
 
        for (int to : E[v]) {
            if (level[to] < level[v]) continue;
 
            int pr = j;
 
            while (j < (int)H.size() && H[j].first == to) {
                int t = H[j].second.first;
                int d = H[j].second.second;
 
                C[col[t]]--;
                sub(S[col[t]], d);
                sub(SQ[col[t]], get(1ll * d * d));
 
                //err("del v =%d, center = %d\n", t, v);
 
                j++;
            }
 
            j = pr;
 
            while (j < (int)H.size() && H[j].first == to) {
                int t = H[j].second.first;
                int d = H[j].second.second;
 
                add(ans, get(1ll * C[col[t]] * d * d));
                add(ans, get(1ll * 2 * d * S[col[t]]));
                add(ans, SQ[col[t]]);
 
                j++;
            }
        }
 
        C[col[v]]--;
    }
 
    printf("%d\n", ans);
    return 0;
}