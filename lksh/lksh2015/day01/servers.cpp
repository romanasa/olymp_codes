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

#define TASK "servers"

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

const int MAXN = 1e5 + 7;

bool ok = true;
int ind[MAXN], ans[MAXN], color[MAXN];
vector<vector<int> > e;

int dfs(int v) {
    color[v] = 1;

    if (ans[v]) {
        color[v] = 2;
        return ans[v];
    }

    if (!e[v].size()) {
        color[v] = 2;
        return 1;
    }

    int cur = 0;
    forn(i, e[v].size()) {
        int to = e[v][i];
        if (color[to] == 1) {
            ok = false;
            return 1;
        }
        if (ind[to] > ind[v])
            cur = max(cur, dfs(to) + 1);
        else
            cur = max(cur, dfs(to));
    }
    color[v] = 2;
    return ans[v] = cur;
}

int solve() {
    int n;
    cin >> n;
    e.resize(n);
    forn(i, n) {
        int v;
        cin >> v;
        ind[v - 1] = i;
    }
    forn(i, n) {
        int k;
        cin >> k;
        forn(j, k) {
            int v; 
            cin >> v;
            e[i].pk(v - 1);
        }
    }
    int res = 0;
    forn(i, n) 
        res = max(res, dfs(i));
    
    if (ok)
        cout << res;
    else
        cout << -1;
    return 0;
}