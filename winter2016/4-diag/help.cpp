#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
#include "grader.h"
 
using namespace std;
 
typedef long long ll;
 
vector<vector<int> > E;
int root;
const int dd = (int)1e5 + 7;
int p[dd], level[dd];
int C[20][dd];
 
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
 
void mark(int v, int pr, int h, int root) {
    C[h][v] = root;
    for (int to : E[v]) {
        if (to != pr && level[to] == -1)
            mark(to, v, h, root);
    }
}
 
void build(int v, int pr, int sz, int h) {
    int center = -1;
    dfs(v, -1, sz, center);
 
    p[center] = pr;
    level[center] = h;
 
    mark(center, -1, h, center);
 
    for (int to : E[center]) {
        if (level[to] == -1) {
            build(to, center, sz / 2, h + 1);
        }
    }
}
 
 
void init(int n, int *u, int *v) {
 
    E.resize(n);
 
    for (int i = 0; i < n - 1; i++) {
        E[u[i] - 1].push_back(v[i] - 1);
        E[v[i] - 1].push_back(u[i] - 1);
    }
 
    for (int i = 0; i < n; i++)
        p[i] = -1, level[i] = -1;
 
    build(0, -1, n, 0);
 
    for (int i = 0; i < n; i++)
        if (level[i] == 0)
            root = i;
 
    //for (int i = 0; i < n; i++)
    //    err("p[%d] = %d, level[%d] = %d\n", i, p[i], i, level[i]);
}
 
vector<int> G;
int cnt = 0;
 
int calc(int v, int h = 0) {
    for (int to : E[v]) {
        if (level[to] > level[v]) {
            if (is_closer(to + 1, v + 1))
                return calc(C[h + 1][to], h + 1);
        }
    }
    return v;
}
 
int rescue() {
    cnt = 0;
    return calc(root) + 1;
}