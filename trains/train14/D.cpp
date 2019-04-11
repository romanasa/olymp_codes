#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define x first
#define y second

using namespace std;

const int INF = (int)1e9 + 7;

int n, k;
int a[10007];
int dp[51][10007];
int cnt[11][10007];
pair<int, int> p[51][10007];

int main(){
    //freopen("input.txt", "r", stdin);
    freopen("decimation.in", "r", stdin);
    freopen("decimation.out", "w", stdout);
    cin >> n >> k;
    for (int i = 1; i <= n; i++){
        char c;
        cin >> c;
        a[i] = c - '0';
    }
    for (int i = 1; i <= n; i++){
        dp[0][i + 1] = dp[0][i];
        if (a[i] == 1 && i % 10 == 0) dp[0][i + 1]++;
    }

    for (int i = 1; i <= k; i++) for (int j = 0; j <= n + 1; j++) dp[i][j] = INF;
    for (int i = 0; i <= k; i++) for (int j = 0; j <= n + 1; j++) p[i][j] = mp(-1, -1);

    for (int i = 1; i <= k; i++){
        for (int j = 1; j <= n; j++){
            if (dp[i][j] > dp[i - 1][j] + ((i - 1 + j) % 10 == 0)){
                dp[i][j] = dp[i - 1][j] + ((i - 1 + j) % 10 == 0);
                p[i][j] = mp(i - 1, j);
            }
            if (dp[i][j + 1] > dp[i][j] + a[j] * ((i + j) % 10 == 0)){
                dp[i][j + 1] = dp[i][j] + a[j] * ((i + j) % 10 == 0);
                p[i][j + 1] = mp(i, j);
            }
        }
    }

    //for (int i = 0; i <= k; i++){
    //    for (int j = 1; j <= n + 1; j++)
    //        cout << dp[i][j] << ' ';
    //    cout << endl;
    //}

    for (int i = n; i >= 1; i--){
        for (int j = 0; j < 11; j++) cnt[j][i] = cnt[j][i + 1];
        if (a[i] == 1) cnt[i % 10][i]++;
    }

    //for (int i = 1; i <= n; i++){
    //    for (int j = 0; j < 10; j++) cout << cnt[j][i] << ' ';
    //    cout << endl;
    //}

    pair<int, pair<int, int> > ans = mp(INF, mp(-1, -1));
    for (int i = 0; i <= k; i++) for (int j = 1; j <= n + 1; j++){
        ans = min(ans, mp(dp[i][j] + cnt[(10 - (i % 10)) % 10][j], mp(i, j)));
    }
    vector<int> w;
    pair<int, int> pos = ans.y;

    while(1){
        auto now = p[pos.x][pos.y];
        if (now == mp(-1, -1)) break;
        if (now.x != pos.x) w.push_back(now.x + now.y);
        pos = now;
    }

    cout << ans.x << "\n";
    sort(w.begin(), w.end());
    cout << w.size() << ' ';
    for (int x : w) cout << x << ' ';
}
