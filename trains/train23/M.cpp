#include <bits/stdc++.h>

#define ll long long

using namespace std;

int n, m;
int a[2007][2007];
int dd[2007][2007];
int dp[2007][2007];

int main() {
    freopen("bestcomb.in", "r", stdin);
    freopen("bestcomb.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> a[i][j];
    for (int i = 0; i < n; i++){
        for (int j = m - 1; j >= 0; j--){
            if (a[i][j] == 1) dd[i][j] = 0;
            else {
                dd[i][j] = 1;
                if (j != m - 1) dd[i][j] += dd[i][j + 1];
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (a[i][j] == 1){
                dp[i][j] = 0;
            } else {
                dp[i][j] = dd[i][j];
                if (i) dp[i][j] += dp[i - 1][j];
                ans = max(ans, dp[i][j]);
            }
        }
    }
    cout << ans;
}
