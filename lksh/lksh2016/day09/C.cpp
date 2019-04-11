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

#define TASK "rollback"

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
    //freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

const int dd = 2e3 + 7;

pair<int, int> w[dd];
int used[dd], pr[dd], prl[dd];
vector<vector<int> > e;

bool dfs(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int to : e[v]) {
        if (pr[to] == -1 || dfs(pr[to])) {
            pr[to] = v;
            prl[v] = to;
            return true;
        }
    }
    return false;
}

int solve() {
    int n;
    cin >> n;

    e.resize(2 * n);

    forn(i, n) {
        cin >> w[i].first;
        w[i].second = i;
    }

    forn(i, n) {
        int t;
        cin >> t;

        forn(j, t) {
            int to;
            cin >> to;

            e[i].push_back(to - 1 + n);
        }
    }

    sort(w, w + n);
    reverse(w, w + n);

    forn(i, 2 * n)
        pr[i] = prl[i] = -1;

    forn(i, n) {
        forn(j, n + n)
            used[j] = false;
        dfs(w[i].second);
    }

    forn(i, n)
        if (prl[i] != -1) {
            cout << prl[i] - n + 1 << " ";
        } else {
            cout << 0 << " ";
        }

    return 0;
}