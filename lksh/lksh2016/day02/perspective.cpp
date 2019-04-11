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

#define TASK "perspective"

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

const int dd = 1000 + 7;

struct edge {
    int v, to, c, f, back, ok;
};

vector<vector<edge> > E;

void add(int a, int b, int c) {
    int ia = E[b].size(), ib = E[a].size();

    edge cur{a, b, c, 0, ia, 1};
    edge rev{b, a, 0, 0, ib, 0};

    E[a].push_back(cur);
    E[b].push_back(rev);
}

int used[dd];
int N;

int dfs(int v, int t, int cmin) {
    used[v] = true;

    if (v == t)
        return cmin;

    for (auto &e : E[v]) {
        if (e.f < e.c && !used[e.to]) {
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

int findflow(int s, int t) {
    int flow = 0;

    while (1) {

        forn(i, N)
            used[i] = 0;
        int df = dfs(s, t, inf);

        if (!df)
            break;
        flow += df;
    }
    return flow;
}

int A[31][31];    
int n;
vector<int> win(31), cnt(31);

bool check(int m) {
    forn(i, N)
        E[i].clear();


    int s = n, t = n + 1;
    int cur = n + 2;

    forn(i, n) {
        forn(j, n) {
            int c = A[i][j];

            if (c && i && j && i < j) {
                add(s, cur, c);
                add(cur, i, c);
                add(cur, j, c);

                cur++;
            }
        }
    }

    fornn(i, 1, n) {
        add(s, i, win[i]);
        add(i, t, m);
    }

    int flow = findflow(s, t);

    for (auto &e : E[s]) {
        if (e.f < e.c)
            return false;
    }
    return true;
}

int solve() {
    cin >> n;

    N = n * n + n + 7;

    E.resize(N);

    forn(i, n) {
        cin >> win[i];
    }
    forn(i, n) {
        cin >> cnt[i];
    }

    forn(i, n) {
        forn(j, n) {
            cin >> A[i][j];
        }
    }
    
    win[0] += cnt[0];
    check(3);


    int l = -1, r = 100000;

    while (r - l > 1) {
        int m = (l + r) / 2;

        if (check(m)) {
            r = m;
        } else {
            l = m;
        }
    }


    if (win[0] >= r)
        puts("YES");
    else
        puts("NO");

    return 0;
}