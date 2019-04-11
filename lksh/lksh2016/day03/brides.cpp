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

#define TASK "brides"

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
    int v, to, c, f, w, back, ind;
};

vector<vector<edge> > E;

void add(int a, int b, int c, int w, int ind) {
    int ia = E[b].size(), ib = E[a].size();

    edge cur{ a, b, c, 0,  w, ia, ind };
    edge rev{ b, a, 0, 0, -w, ib, -1 };

    E[a].push_back(cur);
    E[b].push_back(rev);
}

int n, m;

ll findflow(int s, int t, int k) {

    ll cost = 0;
    ll flow = 0;

    while (1) {

        vector<int> d(n, inf);
        vector<int> used(n, false);
        vector<pair<int, int> > p(n, { -1, -1 });

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

                if (e.f < e.c && d[e.to] > d[v] + e.w) {

                    p[e.to] = mp(v, i);
                    d[e.to] = d[v] + e.w;

                    if (!used[e.to]) {
                        q.push(e.to);
                        used[e.to] = true;
                    }
                }
            }
        }

        if (p[t].first == -1) {
            break;
        }

        int add = k - flow;

        for (int i = t; p[i].first != -1; i = p[i].first) {
            add = min(add, E[p[i].first][p[i].second].c - E[p[i].first][p[i].second].f);
        }

        for (int i = t; p[i].first != -1; i = p[i].first) {
            auto &e = E[p[i].first][p[i].second];

            cost += 1ll * add * e.w;

            e.f += add;
            E[e.to][e.back].f -= add;
        }

        flow += add;

        if (add == 0)
            break;
    }

    if (flow < k)
        return -1;

    return cost;
}

vector<int> cur;
int used[dd];

bool find(int v, int t) {
    used[v] = true;
    
    if (v == t) {
        return true;
    }

    for (auto &e : E[v]) {
        if (e.f > 0 && e.ind > 0 && !used[e.to]) {
            if (find(e.to, t)) {

                e.f--;

                cur.push_back(e.ind);
                return true;
            }
        }
    }
    return false;
}


int solve() {
    int k;
    cin >> n >> m >> k;

    E.resize(n);

    forn(i, m) {
        int a, b, w;
        cin >> a >> b >> w;

        a--, b--;
        add(a, b, 1, w, i + 1);
        add(b, a, 1, w, i + 1);
    }

    ll ans = findflow(0, n - 1, k);

    if (ans == -1) {
        printf("%d", ans);
        return 0;
    }

    printf("%.10f\n", ans * 1.0 / k);

    forn(i, k) {
        cur.clear();
        forn(i, n)
            used[i] = false;

        find(0, n - 1);

        auto path = cur;
        reverse(all(path));

        cout << path.size() << " ";
        for (int x : path)
            cout << x << " ";
        cout << "\n";
    }

    return 0;
}