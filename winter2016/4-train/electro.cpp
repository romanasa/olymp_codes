#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
  
using namespace std;
  
typedef long long ll;
  
const int dd = (int)4e5 + 7;
  
int head[2 * dd], tail[2 * dd];
int to[2 * dd], nxt[2 * dd];
int nv = dd;
  
void add(int a, int b) {
    to[tail[a]] = b;
    nxt[tail[a]] = nv++;
    tail[a] = nxt[tail[a]];
}
  
int h[dd], p[dd], P[dd];
int C[dd], A[dd];
int up[20][dd];
  
void dfs(int v, int pr) {
    if (v == 0) {
        for (int j = 0; j < 20; j++)
            up[j][v] = 0;
    } else {
        up[0][v] = pr;
        for (int j = 1; j < 20; j++)
            up[j][v] = up[j - 1][up[j - 1][v]];
    }
    h[v] = (pr == -1 ? -1 : h[pr]) + 1;
    p[v] = pr;
    for (int i = head[v]; i != tail[v]; i = nxt[i]) {
        if (to[i] != pr)
            dfs(to[i], v);
    }
}
  
int n, k, c;
int curh;
  
void dfs(int v, int pr, int len, int root) {
    if (C[v] > A[root]) {
        C[v] -= A[root];
        A[root] = 0;
        return;
    } else {
        A[root] -= C[v];
        C[v] = 0;
    }
     
    if (A[root] == 0)
        return;
  
    if (len >= k)
        return;
  
    if (pr != p[v]) {
        dfs(p[v], v, len + 1, root);
        if (A[root] == 0)
            return;
    }
  
    for (int i = head[v]; i != tail[v]; i = nxt[i]) {
        if (to[i] != pr && to[i] != p[v]) {
            dfs(to[i], v, len + 1, root);
            if (A[root] == 0)
                return;
        }
    }
}
  
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
  
  
int main() {
    n = readInt(), k = readInt(), c = readInt();
  
    for (int i = 0; i < n; i++) {
        A[i] = readInt();
    }
  
    for (int i = 0; i < n; i++)
        head[i] = tail[i] = i;
  
    vector<int> deg(n);
         
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        a = readInt(), b = readInt();
  
        add(a - 1, b - 1);
        add(b - 1, a - 1);
        deg[a - 1]++;
        deg[b - 1]++;
    }
     
    int ok = 0;
    for (int i = 0; i < n; i++) {
        ok = max(ok, deg[i]);
    }
     
    if (ok <= 2) {
        int root = 0;
        for (int i = 0; i < n; i++)
            if (deg[i] == 1)
                root = i;
  
        dfs(root, -1);
  
        for (int i = 0; i < n; i++)
            P[i] = i;
  
        sort(P, P + n, [](int a, int b) { return h[a] > h[b]; });
  
  
        set<pair<int, int> > S;
  
        for (int i = 0; i < min(k + 1, n); i++) {
            S.insert({ C[P[i]], P[i] });
        }
  
        int ans = 0;
        for (int ii = 0; ii < n; ii++) {
            int i = P[ii];
  
            while (S.size() && S.rbegin()->first > 0 && S.rbegin()->first <= A[i]) {
                int v = S.rbegin()->second;
  
  
                S.erase({ C[v], v });
                A[i] -= C[v];
                C[v] = 0;
                S.insert({ C[v], v});
            }
  
            if (S.size() && S.rbegin()->first > 0) {
                int v = S.rbegin()->second;
                S.erase({ C[v], v });
                C[v] -= A[i];
                A[i] = 0;
                S.insert({ C[v], v});
            }
  
  
            int q = (A[i] + c - 1) / c;
            ans += q;
  
            int add = q * c - A[i];
  
            if(add) {
                int ind = P[min(ii + k, n - 1)];
                S.erase({ C[ind], ind });
                C[ind] += add;
                S.insert({ C[ind], ind});
  
            }
             
                if (ii + k + 1 < n)
                S.insert({ C[P[ii  + k + 1]], P[ii + k + 1]});
             
            if (ii - k >= 0)
                S.erase({ C[P[ii - k]], P[ii - k]});
             
        }
  
        printf("%d\n", ans);
        return 0;
    }
  
    dfs(0, -1);
  
    for (int i = 0; i < n; i++)
        P[i] = i;
  
    sort(P, P + n, [](int a, int b) { return h[a] > h[b]; });
    int ans = 0;
    p[0] = 0;
  
    for (int i = 0; i < n; i++) {
        int v = P[i];
        int cur = v;
  
        curh = h[v];
  
        int t = k;
  
        for (int j = 19; j >= 0; j--) {
            if (t >= (1 << j)) {
                cur = up[j][cur];
                t -= (1 << j);
            }
        }
  
        dfs(v, -1, 0, v);
  
        int q = (A[v] + c - 1) / c;
        ans += q;
        C[cur] += c * q;
  
        C[cur] -= A[v];
        A[v] = 0;
    }
    printf("%d\n", ans);
    return 0;
}