#include <bits/stdc++.h>

#define ll long long

using namespace std;

int n;
int a[111];
bool dp[111][1007];
int p[111][1007];

int main() {
    freopen("smallnim.in", "r", stdin);
    freopen("smallnim.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    reverse(a, a + n);
    dp[0][0] = 1;
    for (int i = 0; i < n; i++){
        if (i) dp[i][0] = dp[i - 1][a[i - 1]];
        for (int j = 1; j <= a[i]; j++){
            for (int s = 1; s <= j; s++){
                if (dp[i][j - s] == 0){
                    dp[i][j] = 1;
                    p[i][j] = s;
                    break;
                }
            }
        }
    }
    if (dp[n - 1][a[n - 1]]) cout << "YES";
    else cout << "NO";
    if (dp[n - 1][a[n - 1]]){
        cout << endl << p[n - 1][a[n - 1]];
    }
}
