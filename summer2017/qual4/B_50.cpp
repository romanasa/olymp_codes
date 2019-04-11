#include "findpath.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
vector<vector<int> > E;
int n;
 
vector<int> get(vector<int> A, int len, int *q, int *a) {
 
    for (int i = 0; i < n; i++) q[i] = 0;
    for (int x : A) q[x] = 1;
    ask(len);
    vector<int> ans;
    for (int i = 0; i < n; i++) if (a[i])
        ans.push_back(i);
    return ans;
}
 
int solve(int n, int* P, int* Q, int* a) {
 
    if (n <= 1000) {
        E.resize(n);
 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) Q[j] = (i == j);
 
            ask(1);
            for (int j = 0; j < n; j++) if (a[j] && i != j) {
                E[i].push_back(j);
            }
        }
 
        vector<int> d(n, n + 1), p(n, -1);
        queue<int> q;
 
        d[0] = 0;
        q.push(0);
 
        while (q.size()) {
            int v = q.front();
            q.pop();
            for (int to : E[v]) {
                if (d[to] > d[v] + 1) {
                    d[to] = d[v] + 1;
                    p[to] = v;
                    q.push(to);
                }
            }
        }
        int l = d[n - 1];
        //err("l = %d\n", l);
        for (int ind = n - 1; ind != -1; P[l--] = ind, ind = p[ind]);
 
        //for (int i = 0; i <= d[n - 1]; i++) err("%d, ", P[i]);
        return d[n - 1] + 1;
    }
    //assert(0);
 
    ::n = n;
 
    int l = -1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        for (int i = 0; i < n; i++) Q[i] = 0;
        Q[0] = 1;
        ask(m);
        if (a[n - 1])
            r = m;
        else
            l = m;
    }
 
    int len = r + 1;
    P[0] = 0, P[len - 1] = n - 1;
 
    vector<int> cur, used(n);
    cur.push_back(0);
 
    used[0] = 1;
 
    for (int it = 1; it < len - 1; it++) {
 
        vector<int> tmp = get(cur, 1, Q, a), nxt;
        for (int x : tmp) if (!used[x])
            nxt.push_back(x), used[x] = 1;
        //err("it = %d, nxt = {", it); for (int x : nxt) err(" %d,", x); err(" }\n");
 
        int l = 0, r = (int)nxt.size();
 
        while (r - l > 1) {
            int m = (l + r) / 2;
            vector<int> T;
            for (int i = 0; i < m; i++) T.push_back(nxt[i]);
 
            get(T, len - it - 1, Q, a);
 
            if (a[n - 1]) r = m;
            else l = m;
        }
        P[it] = nxt[r - 1];
        cur[0] = P[it];
    }
    return len;
}