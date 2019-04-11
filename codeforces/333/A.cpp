#include <bits/stdc++.h>

using namespace std;

int d[407][407];
int g[407];

struct cond {
    int u, v, t;
    cond() {}
    cond(int u, int v, int t) : u(u), v(v), t(t) {}
    bool operator < (cond b) const {
        return t < b.t;
    }
};

const int inf = 1e9 + 7;
int n, m;

vector<int> bfs(int st, vector<vector<int> > &e) {
    vector<int> d(n, inf);
    d[st] = 0;

    queue<int> q;
    q.push(st);

    while (q.size()) {
        int v = q.front();
        q.pop();

        for (int to : e[v])
            if (d[to] > d[v] + 1) {
                d[to] = d[v] + 1;
                q.push(to);
            }
    }
    return d;
}

vector<vector<int> > e(407), f(407);

int F[407][407];

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        e[a - 1].push_back(b - 1);
        e[b - 1].push_back(a - 1);
        F[a - 1][b - 1] = 1;
        F[b - 1][a - 1] = 1;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!F[i][j]) {
                f[i].push_back(j);
            }


    auto de = bfs(n - 1, e);
    auto df = bfs(n - 1, f);

    int ans = max(de[0], df[0]);
    cout << (ans == inf ? -1 : ans);
}
