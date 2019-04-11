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

#define TASK "points"

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

const int MAXN = 2e4 + 7;
int tmm = 1, used[MAXN], enter[MAXN], up[MAXN], point[MAXN];
vector<vector<int> > e;

void dfs(int v, int p = -1) {
    used[v] = true;
    enter[v] = up[v] = tmm++;
    bool ok = false;
    int cnt = 0;

    forn(i, e[v].size()) {
        int to = e[v][i];
        if (!used[to]) {
            dfs(to, v);
            cnt++;
            if (up[to] >= enter[v]) {
                ok = true;
            }
            up[v] = min(up[v], up[to]);
        }
        else {
            up[v] = min(up[v], enter[to]);
        }
    }
    point[v] = (p == -1 && cnt >= 2) || (p != -1 && ok);
}

int solve() {
    int n, m;
    cin >> n >> m;
    e.resize(n);
    forn(i, m) {
        int a, b;
        cin >> a >> b;
        e[a - 1].pk(b - 1);
        e[b - 1].pk(a - 1);
    }
    forn(i, n)
        if (!used[i])
            dfs(i);

    int ans = 0;
    forn(i, n)
        ans += point[i];
    cout << ans << "\n";
    forn(i, n)
        if (point[i])
            cout << i + 1 << "\n";
    return 0;
}