#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int dd = (int)107;
int p[dd], dp[dd], used[dd];
int n;

vector<vector<pair<int, int> >> E;
vector<vector<int>> E2;

vector<int> dijkstra(int s) {
    vector<int> d(n, (int)1e9), used(n);
    d[s] = 0;
    for (int it = 0; it < n; it++) {
        int ind = -1;
        for (int i = 0; i < n; i++) if (!used[i] && d[i] != (int)1e9 && (ind == -1 || d[i] < d[ind])) ind = i;
        if (ind == -1) break;
        used[ind] = 1;
        for (auto &e : E[ind]) {
            if (d[e.first] > d[ind] + e.second) {
                d[e.first] = d[ind] + e.second;
            }
        }
    }
    return d;
}

int calc(int v) {
    if (used[v]) return dp[v];
    used[v] = 1;
    dp[v] = 0;
    for (int to : E2[v]) dp[v] = max(dp[v], calc(to));
    dp[v] += p[v];
    return dp[v];
}

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#endif
    scanf("%d", &n);

    for (int i = 0; i < n; i++) scanf("%d", &p[i]);

    E.resize(n);
    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        E[a - 1].push_back({ b - 1, c });
        E[b - 1].push_back({ a - 1, c });
    }

    auto d1 = dijkstra(0);
    auto d2 = dijkstra(n - 1);

    if (d1[n - 1] == (int)1e9) return 0 * puts("impossible");

    E2.resize(n);
    for (int v = 0; v < n; v++) {
        for (auto &e : E[v]) {
            if (d1[v] + e.second + d2[e.first] == d1[n - 1])
                E2[v].push_back(e.first);
        }
    }
    printf("%d %d\n", d1[n - 1], calc(0));
    return 0;
}
