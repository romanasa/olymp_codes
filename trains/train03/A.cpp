#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:66777216")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <deque>
#include <cassert>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>
#include <cstring>
#include <sstream>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
 
using namespace std;
 
typedef long long ll;
 
#define TASK "artohlam"
 
const int inf = (int)1e9;
 
int solve();
 
int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    //if (TASK != "")
    //freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
    solve();
    return 0;
}
 
#define err(...) fprintf(stdout, __VA_ARGS__), fflush(stderr)
using namespace std;
 
int nV = 1;
int cV = 0;
 
const int dd = 507;
 
const int maxN = (int)4e6 + 7;
 
int ind[maxN];
int num[maxN];
int lst[maxN];
 
vector<vector<int> > E, ER, EC;
 
void add_edge(int a, int b, int t = 0) {
    E[a].push_back(b);
    ER[b].push_back(a);
    /*
    if (t)
    err("add (%d-->%d)\n", a, b);*/
}
int KK;
 
struct node {
    vector<int> L, R;
    int a, b;
    int beg;
 
    node() {
        L.resize(4 * dd);
        R.resize(4 * dd);
    }
 
    int build(int tl, int tr, int tp, int q = 0, int l = -1, int r = -1) {
        int v = nV++ - beg;
 
        if (tl != tr) {
            int tm = (tl + tr) / 2;
            L[v] = build(tl, tm, tp, q, l, r);
            R[v] = build(tm + 1, tr, tp, q, l, r);
 
            if (tp == 1) {
                add_edge(v + beg, L[v] + beg);
                add_edge(v + beg, R[v] + beg);
            } else {
                add_edge(L[v] + beg, v + beg);
                add_edge(R[v] + beg, v + beg);
            }
        } else {
            if (tp == 1)
                lst[v + beg] = q;
            if (tp == 2)
                add_edge(v + beg - KK, v + beg);
        }
 
        if (l != -1) {
            if (tp == 1) {
                add_edge(v + beg, v + l);
                add_edge(v + beg, v + r);
            } else {
                add_edge(v + l, v + beg);
                add_edge(v + r, v + beg);
            }
        }/*
         err("(%d, %d, %d, %d) === %d, %d\n", a, b, tl, tr, v, v + beg);*/
        return v;
    }
 
    void add(int t, int tl, int tr, int l, int r, int v, int tp) {
        if (l == tl && r == tr) {
            if (tp == 1)
                add_edge(v, t + beg, 1);
            else
                add_edge(t + beg, v, 1);
        } else {
            int tm = (tl + tr) / 2;
            if (r <= tm)
                add(L[t], tl, tm, l, r, v, tp);
            else if (l > tm)
                add(R[t], tm + 1, tr, l, r, v, tp);
            else
                add(L[t], tl, tm, l, tm, v, tp), add(R[t], tm + 1, tr, tm + 1, r, v, tp);
        }
    }
} T[4 * dd];
 
 
int L[4 * dd], R[4 * dd], D[4 * dd];
int n, m, w;
 
int build(int tl, int tr, int tp) {
    int v = nV++;
    int i = cV++;
 
    num[i] = v;
    ind[v] = i;
 
    if (tl != tr) {
        int tm = (tl + tr) / 2;
        L[i] = build(tl, tm, tp);
        R[i] = build(tm + 1, tr, tp);
 
        if (tp == 1) {
            add_edge(v, num[L[i]]);
            add_edge(v, num[R[i]]);
        } else {
            add_edge(num[L[i]], v);
            add_edge(num[R[i]], v);
        }
    }
 
    T[i].a = tl, T[i].b = tr, T[i].beg = nV;
    if (tl == tr)
        D[i] = T[i].build(0, m - 1, tp, 1);
    else
        D[i] = T[i].build(0, m - 1, tp, 0, T[L[i]].beg, T[R[i]].beg);
 
    if (tp == 1)
        add_edge(v, T[i].beg + R[i]);
    else {
        add_edge(T[i].beg + R[i], v);
    }
    /*
    err("(%d, %d, %d, %d) === %d, %d\n", tl, tr, 0, m - 1, i, v);*/
    return i;
}
 
void add(int v, int tl, int tr, int l, int r, int a, int b, int j, int tp) {
    if (tl == l && tr == r) {
        T[v].add(D[v], 0, m - 1, a, b, j, tp);
    } else {
        int tm = (tl + tr) / 2;
        if (r <= tm)
            add(L[v], tl, tm, l, r, a, b, j, tp);
        else if (l > tm)
            add(R[v], tm + 1, tr, l, r, a, b, j, tp);
        else {
            add(L[v], tl, tm, l, tm, a, b, j, tp);
            add(R[v], tm + 1, tr, tm + 1, r, a, b, j, tp);
        }
    }
}
 
int used[maxN];
int col[maxN], good[maxN];
int tin[maxN], dp[maxN];
 
vector<int> H, HC;
void topsort(int v) {
    used[v] = true;
    for (int to : E[v])
        if (!used[to])
            topsort(to);
    H.push_back(v);
}
 
void topsortC(int v) {
    used[v] = true;
    for (int to : EC[v])
        if (!used[to])
            topsortC(to);
    HC.push_back(v);
}
 
void mark(int v, int c) {
    col[v] = c;
 
    if (lst[v]) {
        good[c] = 1;
    }
 
    for (int to : ER[v])
        if (col[to] == 0)
            mark(to, c);
}
 
void dfs(int v) {
    /*err("%d, ", v);*/
    used[v] = true;
    for (int to : EC[v])
        if (!used[to])
            dfs(to);
}
 
int solve() {
 
    E.resize(maxN);
    ER.resize(maxN);
 
    scanf("%d %d %d", &n, &m, &w);
 
    int root1 = build(0, n - 1, 1);
    KK = nV - 1;
    int root2 = build(0, n - 1, 2);
 
    while (w--) {
        int Ax1, Ay1, Ax2, Ay2;
        int Bx1, By1, Bx2, By2;
 
        scanf("%d %d %d %d %d %d %d %d", &Ax1, &Ay1, &Ax2, &Ay2, &Bx1, &By1, &Bx2, &By2);
 
        int v = nV++;
 
        add(root1, 0, n - 1, Bx1, Bx2, By1, By2, v, 1);
        add(root2, 0, n - 1, Ax1, Ax2, Ay1, Ay2, v, 2);
    }
 
    /*for (int i = 0; i < nV; i++) {
    if (!E[i].size()) continue;
    err("%d: ", i);
    for (int to : E[i])
    err("%d, ", to);
    err("\n");
    }*/
 
    for (int i = 1; i < nV; i++)
        if (!used[i])
            topsort(i);
 
    reverse(H.begin(), H.end());
 
    int c = 1;
    for (int x : H) {
        if (col[x] == 0) {
            mark(x, c++);
        }
    }/*
 
     vector<pair<int, int> > TT;
     for (int i = 1; i < nV; i++) TT.push_back({ col[i], i });
     sort(TT.begin(), TT.end());
     for (int i = 1; i < nV; i++)
     err("rev[%d] = %d\n", TT[i - 1].first, TT[i - 1].second);*/
 
    EC.resize(c);
 
    for (int i = 0; i < nV; i++) {
        for (int to : E[i]) {
            if (col[i] != col[to]) {
                EC[col[i]].push_back(col[to]);
            }
        }
    }
 
    fill(used, used + c, 0);
 
    for (int i = 1; i < c; i++)
        if (!used[i])
            topsortC(i);
 
    reverse(HC.begin(), HC.end());
 
    fill(used, used + c, 0);
 
    int ans = 0;
 
    for (int i : HC) {
        if (good[i] && !used[i]) {
            ans++;
            dfs(i);/*
                   err("\n\n");*/
        }
    }
    printf("%d\n", ans);
    return 0;
}