#include <bits/stdc++.h>

using namespace std;

const int dd = (int)5e4 + 7;
int dp1[dd], dp2[dd];

int main() {
    int n, k;
    cin >> n >> k;
    
    if (1ll * k * (k + 1) / 2 > n) return 0 * puts("0");
    
    dp1[0] = 1;
    for (int i = 1; i <= k; i++) {
        for (int j = i; j <= n; j++) {
            dp2[j] = dp1[j - i] + dp2[j - i];
            if (dp2[j] >= (int)1e9 + 7) dp2[j] -= (int)1e9 + 7;
        }
        for (int j = 0; j <= n; j++) {
            dp1[j] = dp2[j];
            dp2[j] = 0;
        }
    }
    cout << dp1[n];
    return 0;
}