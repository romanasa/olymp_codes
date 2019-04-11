#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int dd = (int)5e3 + 7;
ll dp[dd][dd];

void upd(ll &a, ll b) { if (a > b) a = b;}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif
    int n, A, B;
    cin >> n >> A >> B;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    for (int i = 0; i < dd; i++) fill(dp[i], dp[i] + dd, (ll)1e18);

    dp[0][0] = 0;
    for (int i = 0; i <= B - A + 1; i++) {
        for (int j = 0; j <= n; j++) {
            if (j < n) upd(dp[i][j + 1], dp[i][j]);
            if (i <= B - A && j < n) upd(dp[i + 1][j + 1], dp[i][j] + abs(a[j] - (i + A)));
        }
        //for (int j = 0; j <= n; j++) cout << dp[i][j] << ", ";
        //cout << "\n";
    }


    cout << dp[B - A + 1][n] << "\n";
}
