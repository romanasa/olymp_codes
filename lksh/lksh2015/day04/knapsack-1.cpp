#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:66777216")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <deque>
#include <cassert>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (int i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "knapsack-1"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int INF = (int)2e9 + 1;
const ll LINF = (ll)8e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main()
{
#ifdef _DEBUG
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

int dp[107][10007], w[107], c[107], p[107][10007];

int solve() {
    int n, s;
    cin >> n >> s;
    fornn(i, 1, n + 1)
        cin >> w[i] >> c[i];

    forn(i, n + 1)
        forn(j, s + 1)
            dp[i][j] = -INF, p[i][j] = -1;

    dp[0][0] = 0;

    for (int i = 1; i <= n; i++)
        for (int cur = 0; cur <= s; cur++) {
            if (cur >= w[i] && dp[i - 1][cur - w[i]] != -INF && 
                dp[i - 1][cur - w[i]] + c[i] > dp[i - 1][cur])
                dp[i][cur] = dp[i - 1][cur - w[i]] + c[i], p[i][cur] = i;
            else
                dp[i][cur] = dp[i - 1][cur];
        }
    int res = 0;
    forn(i, s + 1)
        if (dp[n][i] > dp[n][res])
            res = i;

    vector<int> ans;
    int i = n, j = res;
    while (i) {
        if (dp[i][j] != dp[i - 1][j]) {
            ans.pk(p[i][j]);
            j -= w[p[i][j]];
        }
        i--;
    }
    cout << dp[n][res] << "\n" << ans.size() << "\n";
    for (int x: ans)
        cout << x << " ";
    return 0;
}