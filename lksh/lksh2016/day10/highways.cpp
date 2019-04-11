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

#define TASK "highways"

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

struct edge {
    int a, b, c;
};

vector<edge> E;

struct dsu {
    int R[dd], P[dd];

    void init() {
        forn(i, dd)
            P[i] = i, R[i] = 1;
    }

    int get(int v) {
        return v == P[v] ? v : P[v] = get(P[v]);
    }

    void un(int a, int b) {
        a = get(a), b = get(b);

        if (a != b) {
            if (R[b] > R[a]) {
                swap(a, b);
            }

            P[b] = a;
            R[a] += R[b];
        }
    }
} J;

const int maxE = 5000 + 7;

int H[maxE];
int T[2 * dd];

int solve() {
    int n, m;
    scanf("%d %d", &n, &m);

    E.resize(m);

    forn(i, m) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        E[i] = { a, b, c };
    }
    
    forn(i, m) {
        H[i] = 2;
    }

    vector<vector<int> > G(m);

    while (1) {

        vector<int> A, B;

        forn(i, m) {
            if (H[i] == 1)
                A.push_back(i);
            else
                B.push_back(i);
        }

        memset(T, 0, sizeof(int) * 2 * dd);
        forn(i, m) {
            G[i].clear();
        }

        J.init();
        for (int x : A) {
            J.un(E[x].a, E[x].b);
            T[E[x].c]++;
        }

        queue<int> q;
        vector<int> d(m, inf), p(m, -1);

        for (int x : B) {
            if (J.get(E[x].a) != J.get(E[x].b)) {
                q.push(x);
                d[x] = 0;
            }
        }

        for (int v : A) {
            for (int u : B) {
                T[E[v].c]--;
                T[E[u].c]++;

                if (T[E[v].c] < 2 && T[E[u].c] < 2) {
                    G[u].push_back(v);
                }

                T[E[v].c]++;
                T[E[u].c]--;
            }
        }

        for (int v : A) {
            J.init();
            for (int x : A) {
                if (x != v)
                    J.un(E[x].a, E[x].b);
            }
            for (int x : B) {
                if (J.get(E[x].a) != J.get(E[x].b))
                    G[v].push_back(x);
            }
        }

        while (q.size()) {
            int v = q.front();
            q.pop();

            for (int to : G[v]) {
                if (d[to] > d[v] + 1) {
                    d[to] = d[v] + 1;
                    p[to] = v;
                    q.push(to);
                }
            }
        }

        int mx = inf, ind = -1;

        for (int x : B) {
            if (T[E[x].c] + 1 < 2 && d[x] < mx) {
                mx = d[x];
                ind = x;
            }
        }

        if (mx == inf)
            break;

        for (int v = ind; v != -1; v = p[v]) {
            H[v] = 3 - H[v];
        }
    }

    int ans = 0;
    forn(i, m)
        ans += H[i] == 1;

    printf("%d\n", ans);
    forn(i, m)
        if (H[i] == 1)
            printf("%d ", i + 1);
    return 0;
}