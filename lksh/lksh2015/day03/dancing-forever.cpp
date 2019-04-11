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

#define TASK "dancing-forever"

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

const int MAXN = 2e5 + 7;
int used[MAXN], pr[MAXN], prl[MAXN], is[1007][1007], was[MAXN], tmm = 1;
vector<vector<int> > e;

void dfs(int v, int left) {
    used[v] = 1;
    for (int to : e[v]) {
        if (is[v][to] && !left) {
            if (!used[to])
                dfs(to, left ^ 1);
        }
        if (!is[v][to] && left) {
            if (!used[to])
                dfs(to, left ^ 1);
        }
    }
}

bool kuhn(int v) {
    if (used[v] == tmm) return false;
    used[v] = tmm;
    for (int to : e[v])
        if (pr[to] == -1 || kuhn(pr[to])) {
            pr[to] = v, prl[v] = to;
            return true;
        }

    return false;
}

int solve() {
    string s;
    cin >> s;
    int n = (int)sqrt(s.size());
    e.resize(n + n + 7);
    forn(i, s.size()) {
        int x = i / n, y = i % n + n;
        if (s[i] == 'Y') {
            e[x].pk(y);
            e[y].pk(x);
        }
    }
    forn(i, n + n)
        pr[i] = -1, used[i] = 0;

    forn(i, n) {
        tmm++;
        kuhn(i);
    }

    int ans = 0;
    fornn(i, n, n + n) {
        if (pr[i] != -1)
            was[i] = was[pr[i]] = is[i][pr[i]] = is[pr[i]][i] = 1, ans++;
    }

    if (ans == n) {
        fornn(i, n, n + n)
            cout << pr[i] + 1 << " " << i - n + 1 << "\n";
    }
    else {
        forn(i, n + n)
            used[i] = 0;

        forn(i, n)
            if (!was[i])
                dfs(i, 1);

        forn(i, n)
            if (was[i] && used[i])
                cout << i + 1 << " " << prl[i] + 1 - n << "\n";
    }

    return 0;
}