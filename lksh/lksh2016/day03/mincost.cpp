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

#define TASK "mincost"

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
    int v, to, c, f, w, back;
};

vector<vector<edge> > E;

void add(int a, int b, int c, int w) {
    int ia = E[b].size(), ib = E[a].size();

    edge cur{ a, b, c, 0,  w, ia };
    edge rev{ b, a, 0, 0, -w, ib };

    E[a].push_back(cur);
    E[b].push_back(rev);
}

int n, m;

ll fb(int s, int t) {
    vector<int> d(n, inf);
    vector<int> used(n, false);
    vector<pair<int, int> > p(n, {-1, -1 });

    queue<int> q;

    q.push(s);
    used[s] = true;
    d[s] = 0;

    while (q.size()) {
        int v = q.front();

        used[v] = false;
        q.pop();

        forn(i, E[v].size()) {

            auto &e = E[v][i];

            if (e.f < e.c && d[e.to] > d[v] + e.w ) {

                p[e.to] = mp(v, i);
                d[e.to] = d[v] + e.w;

                if (!used[e.to]) {
                    q.push(e.to);
                    used[e.to] = true;
                }
            }
        }
    }

    int add = inf;
    ll cost = 0;

    for (int i = t; p[i].first != -1; i = p[i].first) {
        add = min(add, E[p[i].first][p[i].second].c - E[p[i].first][p[i].second].f);
    }

    for (int i = t; p[i].first != -1; i = p[i].first) {
        auto &e = E[p[i].first][p[i].second];

        cost += 1ll * add * e.w;

        e.f += add;
        E[e.to][e.back].f -= add;
    }

    return cost;
}

ll findflow(int s, int t) {
    ll cost = 0;
    while (1) {
        ll dc = fb(s, t);
        if (!dc)
            break;
        cost += dc;
    }
    return cost;
}

int solve() {
    cin >> n >> m;

    E.resize(n);

    forn(i, m) {
        int a, b, c, w;
        cin >> a >> b >> c >> w;

        a--, b--;
        add(a, b, c, w);
    }

    ll ans = findflow(0, n - 1);

    cout << ans;
    return 0;
}