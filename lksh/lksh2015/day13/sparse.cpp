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
#include <unordered_set>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (ll i = 0; i < (ll)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "sparse"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int inf = (int)2e9 + 1;
const ll linf = (ll)9e18 + 7;
const ll MM = (ll)1e9 + 7;

int solve();

int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

const int MAXN = 1e5 + 7;
ll a[MAXN], dp[23][MAXN];
int lg[MAXN];

int solve() {
    forn(i, MAXN)
        lg[i] = (int)(log2(i));
    
    int n, m;

    cin >> n >> m >> a[0];

    /*forn(i, n)
        cin >> a[i];*/

    forn(i, n - 1)
        a[i + 1] = (23 * a[i] + 21563) % 16714589;

    forn(i, n)
        dp[0][i] = a[i];

    for (int k = 1; (1 << k) <= n; k++) {
        for (int i = 0; i < n - (1 << k) + 1; i++)
            dp[k][i] = min(dp[k - 1][i], dp[k - 1][i + (1 << (k - 1))]);
    }

    int u, v, nu, nv, ans, cur;
    cin >> nu >> nv;

    forn(i, m) {
        u = nu, v = nv;

        int l = min(u, v), r = max(u, v);
        cur = lg[r - l + 1];
        ans = min(dp[cur][l - 1], dp[cur][r - (1 << cur)]);
        
        nu = (17 * u + 751 + ans + 2 * (i + 1)) % n + 1;
        nv = (13 * v + 593 + ans + 5 * (i + 1)) % n + 1;
    }

    cout << u << " " << v << " " << ans;
    return 0;
}