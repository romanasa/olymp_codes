#include <bits/stdc++.h>

#define ll long long

using namespace std;

int n;
ll dp[33][33];
int func[33][33];

int getSum(ll x){
    int ans = 0;
    while(x){
        ans += x % 10;
        x /= 10;
    }
    return ans;
}

int main() {
    freopen("pinball.in", "r", stdin);
    freopen("pinball.out", "w", stdout);
    cin >> n;
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) for (int j = 0; j <= i; j++){
        dp[i][j] = dp[i - 1][j];
        if (j != 0) dp[i][j] += dp[i - 1][j - 1];
    }
    func[0][0] = 1;

    for (int i = 1; i <= n; i++) for (int j = 0; j <= i; j++){
        func[i][j] = func[i - 1][j];
        if (j != 0) func[i][j] = max(func[i][j], func[i - 1][j - 1]);
        func[i][j] += getSum(dp[i][j]);
    }

    int ans = 0;
    for (int i = 0; i <= n; i++) ans = max(ans, func[n][i]);
    cout << ans;
}
