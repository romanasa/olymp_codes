#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
const int INF = 300;
#else
const int INF = 1e9;
#endif

// -*-*-* All variables *-*-*-
vector<vector<pair<int, int>>> dp; // amount of completed, len in last
int x, a, y, b, l;

// -*-*-* All functions *-*-*-
bool check(int m) {
    dp.assign(x + 1, vector<pair<int, int>>(y + 1, {0, 0}));
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            if (i) {
                auto tmp = dp[i - 1][j];
                tmp.second += a;
                if (tmp.first != l && tmp.second >= m) {
                    tmp.first++;
                    tmp.second = 0;
                }
                dp[i][j] = max(dp[i][j], tmp);
            }
            if (j) {
                auto tmp = dp[i][j - 1];
                tmp.second += b;
                if (tmp.first != l && tmp.second >= m) {
                    tmp.first++;
                    tmp.second = 0;
                }
                dp[i][j] = max(dp[i][j], tmp);
                if (dp[i][j].first >= l) return 1;
            }
        }
    }
    return 0;
}
int bin_search() {
    int l = 0, r = INF;
    while (r - l > 1) {
        int m = (l + r) / 2;
        int ans = check(m);
        // cerr << m << ' ' << ans << '\n';
        if (ans) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}
void init() {}

void solve() {
    // cout << check(9) << '\n';
    cout << bin_search() << '\n';
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    string taskName = "B";
    freopen((taskName + ".in").c_str(), "r", stdin);
    freopen((taskName + ".out").c_str(), "w", stdout);
    clock_t start = clock();
#else
    string taskName = "";
// freopen((taskName + ".in").c_str(), "r", stdin);
// freopen((taskName + ".out").c_str(), "w", stdout);
#endif
    while (cin >> x >> a >> y >> b >> l) {
        solve();
#ifdef LOCAL
        cerr << "Elapsed " << setprecision(4) << fixed
             << (clock() - start * 1.) / CLOCKS_PER_SEC << '\n';
#endif
    }
}