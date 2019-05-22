#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
#define TASK "twopaths"
 
const int dd = (int)4e5 + 7;
 
int tmm = 1;
int tin[dd], tout[dd], h[dd];
int p[dd];
 
int A[dd], B[dd];
int LOG[2 * dd];
int F[dd], L[dd];
 
vector<pair<int, int> > st[dd], fn[dd];
pair<int, int> S[20][dd]; 
 
vector<vector<int> > E;
vector<pair<int, int> > T;
 
 
int get(int l, int r) {
    //return min_element(T.begin() + l, T.begin() + r + 1)->second;
    int t = LOG[r - l + 1];
    return min(S[t][l], S[t][r - (1 << t) + 1]).second;
}
 
void dfs(int v, int d) {
    tin[v] = tmm++;
    h[v] = d;
 
    T.push_back({ h[v], v });
    F[v] = L[v] = (int)T.size() - 1;
     
    for (int to : E[v]) {
        dfs(to, d + 1);
        T.push_back({ h[v], v });
        L[v] = (int)T.size() - 1;
    }
         
    tout[v] = tmm++;
}
 
void build() {
    for (int i = 0; i < (int)T.size(); i++) {
        S[0][i] = T[i];
    }
     
    for (int k = 1; (1 << k) <= (int)T.size(); k++) {
        for (int i = 0; i + (1 << k) - 1 < (int)T.size(); i++) {
            S[k][i] = min(S[k - 1][i], S[k - 1][i + (1 << (k - 1))]);
        }   
    }
}
 
inline bool par(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}
 
int lca(int a, int b) {
    if (par(a, b))
        return a;
     
    if (par(b, a))
        return b;
         
    if (L[a] <= F[b]) 
        return get(L[a], F[b]);
    return get(L[b], F[a]);
}
 
int ans = 0, indI = 0, indJ = 1;
 
void upd(int i, int j) {
    if (i == j)
        return;
    int vi = lca(A[i], B[i]);
    int vj = lca(A[j], B[j]);
     
    //err("\n");
    //err("(%d -- %d -- %d), (%d -- %d -- %d)\n", A[i], vi, B[i], A[j], vj, B[j]);
     
    int cur = 0;
     
    if (par(vi, A[j]) && par(vj, A[i])) {
        int k = lca(A[i], A[j]);
        int l = (h[vi] > h[vj] ? vi : vj);
         
        //err("(%d, %d), ", l, k);
         
        cur += max(h[k] - h[l], 0);
    }
     
    if (par(vi, B[j]) && par(vj, A[i])) {
        int k = lca(A[i], B[j]);
        int l = (h[vi] > h[vj] ? vi : vj);
         
         
        cur += max(h[k] - h[l], 0);
    }
     
    if (par(vi, A[j]) && par(vj, B[i])) {
        int k = lca(B[i], A[j]);
        int l = (h[vi] > h[vj] ? vi : vj);
         
         
        cur += max(h[k] - h[l], 0);
    }
     
    if (par(vi, B[j]) && par(vj, B[i])) {
        int k = lca(B[i], B[j]);
        int l = (h[vi] > h[vj] ? vi : vj);
         
 
        cur += max(h[k] - h[l], 0);
    }
     
     
    if (ans < cur) {
        ans = cur;
        indI = i, indJ = j;
    }
}
 
set<pair<int, int> > calc(int v) {
    set<pair<int, int> > cur;
     
    for (auto x : fn[v]) {  
        auto it = cur.insert(x).first;
        if (it != cur.begin()) {
            --it;
            upd(x.second, it->second);
            ++it;
        }
        if (++it != cur.end()) {
            upd(x.second, it->second);
        }
         
    }
     
    for (int to : E[v]) {
        auto t = calc(to);
        if (t.size() > cur.size())
            t.swap(cur);
         
        for (auto x : t) {
            auto it = cur.insert(x).first;
            if (it != cur.begin()) {
                --it;
                upd(x.second, it->second);
                ++it;
            }
            if (++it != cur.end()) {
                upd(x.second, it->second);
            }
        }
    }
     
    return cur;
}
 
int main() {
#ifndef HOME
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
 
    int n, k;
    scanf("%d %d", &n, &k);
     
    E.resize(n);
     
    LOG[1] = 0;
    for (int i = 2; i <= 2 * n; i++) {
        LOG[i] = LOG[i >> 1] + 1;
    }
     
    for (int i = 0; i < n - 1; i++) {
        int t;
        scanf("%d", &t);
        E[t - 1].push_back(i + 1);
        p[i + 1] = t - 1;
    }
     
    dfs(0, 0);
    build();
     
    //err("T: "); for (auto c : T) err("(%d, %d), ", c.first, c.second); err("\n");
     
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &A[i], &B[i]);
        A[i]--, B[i]--;
         
        fn[A[i]].push_back({ tin[B[i]], i });    
        fn[B[i]].push_back({ tin[A[i]], i });
    }
     
    /*
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < i; j++) {
            upd(i, j);
        }
    }*/
     
    calc(0);
     
    printf("%d\n%d %d\n", ans, indI + 1, indJ + 1);
    return 0;
}