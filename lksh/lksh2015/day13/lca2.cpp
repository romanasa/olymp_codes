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

#define TASK "lca2"

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

const int MAXN = 2e5 + 7;
const int MAXC = 2e7 + 7;

pair<int, int> dp[23][MAXN];
int lg[MAXN], used[MAXN], first[MAXN];

ll a[MAXC];

vector<vector<int> > e;
vector<pair<int, int> > euler;

void dfs(int v, int curh = 1) {
    used[v] = true;
    first[v] = euler.size();
    euler.pk({curh, v});

    for (int to : e[v]) {
        if (!used[to]) {
            dfs(to, curh + 1);
            euler.pk({curh, v});
        }
    }
}

int solve() {
    forn(i, MAXN)
        lg[i] = (int)(log2(i));
    
    int n, m;

    cin >> n >> m;
    e.resize(n);

    fornn(i, 1, n) {
        int v;
        cin >> v;
        e[v].pk(i);
    }
    
    dfs(0);

    int N = euler.size();
    forn(i, N)
        dp[0][i] = euler[i];

    for (int k = 1; (1 << k) <= N; k++) {
        for (int i = 0; i < N - (1 << k) + 1; i++)
            dp[k][i] = min(dp[k - 1][i], dp[k - 1][i + (1 << (k - 1))]);
    }

    ll cur, x, y, z, res = 0;
    pair<int, int> ans;
    cin >> a[1] >> a[2] >> x >> y >> z;

    fornn(i, 3, 2 * m + 1)
        a[i] = (x * a[i - 2] + y * a[i - 1] + z) % n;

    fornn(i, 1, m + 1) {    

        int u, v;
        if (i == 1)
            u = a[1], v = a[2];
        else
            u = (a[2 * i - 1] + ans.second) % n, v = a[2 * i]; 

        int l = min(first[u], first[v]), r = max(first[u], first[v]);

        cur = lg[r - l + 1];
        ans = min(dp[cur][l], dp[cur][r - (1 << cur) + 1]);
        
        res += (ll)ans.second;
    }

    cout << res;
    return 0;
}