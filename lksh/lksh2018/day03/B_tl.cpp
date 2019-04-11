#include <bits/stdc++.h>

using namespace std;

/*class line {
public:
    double x;
    double dp, b;

};*/


int main() {

    //vector < line > a;
    int n;
    cin >> n;
    long long dp[n + 1], a[n], b[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    dp[0] = 0;
    int u = 0;
    for (int i = 1; i < n; i++) {
        dp[i] = dp[u] + a[i] * b[u];
        while (u < i - 1) {
            u++;
            if(dp[i] > dp[u] + a[i] * b[u]) dp[i] = dp[u] + a[i] * b[u];
            else {
                u--;
                break;
            }
        }
        //cout << dp[i] << endl;
    }
    cout << dp[n - 1];

}