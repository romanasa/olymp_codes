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

int n;
int a[100007];
int b[100007];
int dp[100007][3];

int getType(int v){
    if (a[v] == 1 && b[v] == 1) return 0;
    if (a[v] == 1 && b[v] == 0) return 1;
    if (a[v] == 0 && b[v] == 1) return 2;
    if (a[v] == 0 && b[v] == 0) return -1;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    for (int i = 0; i < 100007; i++) for (int j = 0; j < 3; j++) dp[i][j] = -1;

    dp[0][0] = 0;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < 3; j++) dp[i + 1][j] = dp[i][j];
        int type = getType(i);
        if (type == -1) continue;
        if (type == 0){
            if (dp[i][0] != -1) dp[i + 1][0] = max(dp[i + 1][0], dp[i][0] + 1);
            if (dp[i][1] != -1) dp[i + 1][0] = max(dp[i + 1][0], dp[i][1] + 1);
            if (dp[i][2] != -1) dp[i + 1][0] = max(dp[i + 1][0], dp[i][2] + 1);
        }
        if (type == 1){
            if (dp[i][0] != -1) dp[i + 1][1] = max(dp[i + 1][1], dp[i][0] + 1);
            if (dp[i][2] != -1) dp[i + 1][1] = max(dp[i + 1][1], dp[i][2] + 1);
        }
        if (type == 2){
            if (dp[i][0] != -1) dp[i + 1][2] = max(dp[i + 1][2], dp[i][0] + 1);
            if (dp[i][1] != -1) dp[i + 1][2] = max(dp[i + 1][2], dp[i][1] + 1);
        }
    }

    cout << max(dp[n][0], max(dp[n][1], dp[n][2]));
}

