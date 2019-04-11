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
#include <cstring>
#include <sstream>
#include <numeric>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "flow"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll INF = (ll)2e9 + 1;
const ll LINF = (ll)8e18;
const ll inf = (ll)2e9 + 1;
const ll linf = (ll)8e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

const int dd = 100 + 7;

int used[dd];

struct edge {
    int v, to, c, f, back, ind;
};


vector<vector<edge> > E;

int dfs(int v, int minc, int t) {
    used[v] = true;
    if (v == t)
        return minc;

    for (auto &e : E[v]) {
        if (e.f < e.c && !used[e.to]) {
            int df = dfs(e.to, min(minc, e.c - e.f), t);
            if (df) {
                e.f += df;
                E[e.to][e.back].f -= df;

                return df;
            }
        }
    }
    return 0;
}

int solve() {
    int n, m;
    cin >> n >> m;

    E.resize(n);

    forn(i, m) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;

        int ia = E[b].size(), ib = E[a].size();

        edge cur{ a, b, c, 0, ia, i };
        edge rev{ b, a, c, 0, ib, -1 };

        E[a].push_back(cur);
        E[b].push_back(rev);

    }

    int f = 0;
    while (1) {
        forn(i, n)
            used[i] = false;

        int df = dfs(0, inf, n - 1);
        if (!df)
            break;

        f += df;
    }

    vector<int> ans(m);

    forn(v, n) {
        for (auto e : E[v]) {
            if (e.ind >= 0) {
                ans[e.ind] = e.f;
            }
        }
    }

    cout << f << "\n";

    forn(i, m)
        cout << ans[i] << "\n";
    
	return 0;
}