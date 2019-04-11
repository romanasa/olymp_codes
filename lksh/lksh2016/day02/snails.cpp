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

#define TASK "snails"

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

struct edge {
    int v, to, c, f, back;
};

vector<vector<edge> > E;

void add(int a, int b, int c) {
    int ia = E[b].size(), ib = E[a].size();

    edge cur{ a, b, c, 0, ia};
    edge rev{ b, a, 0, 0, ib};

    E[a].push_back(cur);
    E[b].push_back(rev);
}

int used[dd];

vector<int> cur;

int dfs(int v, int minc, int t) {
    used[v] = true;

    if (v == t) {
        return minc;
    }

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

bool find(int v, int t) {
    used[v] = true;

    if (v == t) {
        cur.push_back(v);
        return true;
    }

    for (auto &e : E[v]) {
        if (e.f > 0 && !used[e.to]) {
            int df = find(e.to, t);

            if (df) {
                e.f = 0;
                cur.push_back(v);

                return df;
            }
        }
    }
    return false;
}

int solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--, t--;

    E.resize(n);

    forn(i, m) {
        int a, b;
        cin >> a >> b;
        a--, b--;

        add(a, b, 1);
    }


    dfs(s, 10, t);
    forn(i, n)
        used[i] = false;
    dfs(s, 10, t);


    forn(i, n)
        used[i] = false;
    find(s, t);

    auto path1 = cur;

    cur.clear();

    forn(i, n)
        used[i] = false;
    find(s, t);
    
    auto path2 = cur;

    reverse(all(path1));
    reverse(all(path2));

    if (path1.size() && path2.size()) {
        puts("YES");
        for (int x : path1)
            cout << x + 1 << " ";
        cout << "\n";
        for (int x : path2)
            cout << x + 1 << " ";
    } else {
        puts("NO");
    }

	return 0;
}