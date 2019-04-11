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

#define TASK "flow2"

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

const int dd = 500 + 7;

struct edge {
    int v, to, c, f, back;
};

vector<vector<edge> > E;

void add(int a, int b, int c) {
    int ia = E[b].size(), ib = E[a].size();

    edge cur{ a, b, c, 0, ia };
    edge rev{ b, a, 0, 0, ib };

    E[a].push_back(cur);
    E[b].push_back(rev);
}

int n, m, B;
int head[dd], d[dd];

int bfs(int s, int t) {
    forn(i, n)
        d[i] = 507;

    queue<int> q;

    q.push(s);
    d[s] = 0;

    while (q.size()) {
        int v = q.front();
        q.pop();

        for (auto &e : E[v]) {
            if (e.c - e.f >= B && d[e.to] > d[v] + 1) {
                d[e.to] = d[v] + 1;
                q.push(e.to);
            }
        }
    }
    return (d[t] == 507 ? -1 : 1);
}

int dfs(int v, int t, int cmin) {

    if (v == t)
        return cmin;

    for (; head[v] < E[v].size(); head[v]++) {

        auto &e = E[v][head[v]];

        if (d[e.to] == d[v] + 1 && e.c - e.f >= B) {
            int df = dfs(e.to, t, min(cmin, e.c - e.f));

            if (df) {

                e.f += df;
                E[e.to][e.back].f -= df;

                return df;
            }
        }
    }
    return 0;

}

ll dinic(int s, int t) {
    ll flow = 0;

    for (B = 1 << 30; B; B /= 2) {


        while (bfs(s, t) != -1) {

            memset(head, 0, sizeof(int) * n);

            while (1) {
                int df = dfs(s, t, inf);

                if (!df)
                    break;

                flow += df;
            }
        }
    }
    return flow;
}

int solve() {
    cin >> n >> m;

    E.resize(n);

    forn(i, m) {
        int a, b, c;
        cin >> a >> b >> c;

        a--, b--;

        add(a, b, c);
    }

    cout << dinic(0, n - 1);
    return 0;
}