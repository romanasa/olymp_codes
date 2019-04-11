#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

int G[31][31];
int dp[(1 << 20) + 7];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> G[i][j];

    fill(dp, dp + (1 << n), (int)1e9);

    dp[(1 << n) - 1] = 0;
    int ans = (int)1e9;

    for (int msk = (1 << n) - 1; msk > 0; msk--) {
        int cnt = 0;
        for (int i = 0; i < n; i++) if ((msk >> i) & 1) {
            cnt++;
            int cur = (int)1e9;
            for (int j = 0; j < n; j++) if (((msk >> j) & 1) && i != j)
                cur = min(cur, G[i][j]);
            dp[msk ^ (1 << i)] = min(dp[msk ^ (1 << i)], dp[msk] + cur);
        }
        if (cnt <= k) ans = min(ans, dp[msk]);
    }
    cout << ans << "\n";

    return 0;
}

