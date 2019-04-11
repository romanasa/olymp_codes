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

#define forn(i, n) for (ll i = 0; i < (ll)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "trader"

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
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    //freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

int n;
pair<int, int> ans = { INF, -1 };
vector<vector<pair<int, int> > > e;
vector<int> path, res;

const int LOG = 19;
int dp[1 << LOG][LOG];
pair<int, int> p[1 << LOG][LOG];

int solve() {
    cin >> n;
    e.resize(n);
    forn(i, n) {
        forn(j, n) {
            int v;
            cin >> v;
            if (v)
                e[i].pk({ j, v });
        }
    }

    forn(i, 1 << n)
        forn(j, n)
        dp[i][j] = INF;

    //dp[1][0] = 0;
    for (int i = 0; i < n; i++) dp[(1 << i)][i] = 0, p[(1 << i)][i] = { -1, i };

    forn(msk, (1 << n))
        forn(v, n) {
        if (dp[msk][v] == INF)
            continue;
        for (auto pr : e[v]) {
            int to = pr.first, c = pr.second;
            if (!(msk & (1 << to))) {
                if (dp[msk | (1 << to)][to] > dp[msk][v] + c)
                    dp[msk | (1 << to)][to] = dp[msk][v] + c, p[msk | (1 << to)][to] = mp(v, to);
            }
        }
    }

    int ind = 0, fmask = (1 << n) - 1;
    forn(v, n) {
        if (dp[fmask][v] < dp[fmask][ind])
            ind = v;
    }
    if (dp[fmask][ind] == INF) {
        cout << -1;
        return 0;
    }
    cout << dp[fmask][ind] << "\n";

    vector<int> res;
    int i = fmask, j = ind;
    while (i) {
        auto f = p[i][j];
        int v = f.first, to = f.second;
        res.pk(to);
        i -= (1 << to), j = v;
    }
    reverse(all(res));
    for (int x : res)
        cout << x + 1 << " ";
    return 0;
}