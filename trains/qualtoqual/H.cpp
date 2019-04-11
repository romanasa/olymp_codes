#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#define x first
#define y second
#define mp make_pair
#define pub push_back
#define all(v) (v).begin(), (v).end()

using namespace std;

typedef long long ll;
typedef double db;

const int dd = (int)5e3 + 7;
int dp[dd];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN

    int n;
    cin >> n;

    vector<int> t(n + 2);
    for (int i = 0; i < n; i++) cin >> t[i + 1];
    t[n + 1] = (int)1e9;

    fill(dp, dp + n + 1, (int)1e9);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int cur = 0;
        int ind = -1;

        if (dp[i - 1] == (int)1e9) continue;

        for (int j = i; j <= n; j++) {
            if (t[j] - 20 * (j - i) > cur) {
                cur = t[j] - 20 * (j - i);
                ind = j;
            }
            int st = min(t[i] + 30 * 60, cur);
            int fin = t[ind] + (j - ind + 1) * 20;

            err("st = %d, fin = %d\n", st, fin);
            if (fin + 120 <= t[j + 1]) {
                dp[j] = min(dp[j], dp[i - 1] + fin + 60 - st + 60);
            }
        }
    }
    for (int i = 0; i <= n; i++) err("dp[%d] = %d\n", i, dp[i]);
    cout << dp[n];
    return 0;
}

