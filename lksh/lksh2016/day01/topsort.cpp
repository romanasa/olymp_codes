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

#define TASK "topsort"

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

const int dd = 1e5 + 7;

vector<vector<int> > e;
vector<int> ans;

int color[dd];
bool ok = true;

void dfs(int v) {
    color[v] = 1;

    for (int to : e[v]) {
        if (color[to] == 1)
            ok = false;
        if (!color[to])
            dfs(to);
    }

    ans.push_back(v);
    color[v] = 2;
}

int solve() {
    int n, m;
    cin >> n >> m;

    e.resize(n);

    forn(i, m) {
        int a, b;
        cin >> a >> b;

        e[a - 1].push_back(b - 1);
    }

    forn(i, n)
        if (!color[i])
            dfs(i);

    if (ok) {
        reverse(all(ans));
        for (int x : ans)
            cout << x + 1 << " ";
    } else {
        cout << -1;
    }
    return 0;
}