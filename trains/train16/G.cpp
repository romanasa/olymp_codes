#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
int a[111];
int b[111];
int ans = 0;
int dp[111][111];
int func[111];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b[j] = a[(i + j) % n];
        }
        for (int s = 0; s < 111; s++) for (int t = 0; t < 111; t++) dp[s][t] = 0;

        for (int j = n - 2; j >= 0; j--){
            for (int s = 0; s < n; s++) func[s] = 0;
            func[j + 1] = abs(b[j] - b[j + 1]);
            for (int s = j + 1; s < n; s++){
                for (int last = j + 1; last < s; last++){
                    func[s] = max(func[s], func[last] + dp[last][s - 1] + abs(b[s] - b[j]));
                }
                for (int last = j + 1; last <= s; last++) dp[j][s] = max(dp[j][s], func[last] + dp[last][s]);
            }
        }
        ans = max(ans, dp[0][n - 1]);
    }

    cout << ans;
}
