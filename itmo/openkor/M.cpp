//
// Created by Administrator on 14.10.2018.
//
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;
#define double long long

using namespace std;

const int dd = (int) 3e5 + 7;

vector<pair<int, double>> G[dd], G1[dd];
int n, k, cnt[dd][2];
double dp[dd][2];

void dfs(int v, double m, int p = -1) {
    dp[v][0] = 0;
    dp[v][1] = -1e18;
    cnt[v][0] = 0, cnt[v][1] = -(int)5e5;
    for (auto to : G[v]) if (to.first != p) {
        dfs(to.first, m, v);
        if (dp[to.first][0] > dp[to.first][1]) {
            dp[v][0] += dp[to.first][0];
            cnt[v][0] += cnt[to.first][0];
        } else {
            dp[v][0] += dp[to.first][1];
            cnt[v][0] += cnt[to.first][1];
        }
    }
    for (auto to : G[v]) if (to.first != p) {
        double cur = dp[v][0];
        int curCnt = cnt[v][0];
        if (dp[to.first][0] <= dp[to.first][1]) {
            cur -= dp[to.first][1];
            curCnt -= cnt[to.first][1];
            cur += dp[to.first][0];
            curCnt += cnt[to.first][0];
        }
        if (dp[v][1] < cur + to.second + m) {
            dp[v][1] = cur + to.second + m;
            cnt[v][1] = curCnt + 1;
        }
    }
}

double get(double m) {
    dfs(0, m);
    if (dp[0][0] > dp[0][1]) {
        return cnt[0][0];
    }
    return cnt[0][1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef SIR
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        int v, u, w;
        cin >> v >> u >> w;
        G[--v].emplace_back(--u, w);
        G[u].emplace_back(v, w);
        G1[v].emplace_back(u, w);
        G1[u].emplace_back(v, w);
    }

    double l = -2e6, r = 1e14;
    while (r - l > 1) {
        double m = (l + r) / 2;
        if (get(m) >= k) {
            r = m;
        } else {
            l = m;
        }
    }

    if (r < 1e13) {
        int nl = get(l);
        double cl = max(dp[0][0], dp[0][1]);

        int nr = get(r);
        double cr = max(dp[0][0], dp[0][1]);

        if (nl == k) cout << (ll)round(cl - l * k) << "\n", exit(0);
        if (nr == k) cout << (ll)round(cr - r * k) << "\n", exit(0);
        //assert(0);
        double cm = cl + (cr - cl) * (k - nl) / (nr - nl);
        cout << (ll)round(cm - k * r) << "\n";
    } else {
        cout << "Impossible\n";
    }
    return 0;
}
