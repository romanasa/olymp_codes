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

#define TASK "molecule"

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
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    //freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
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
int N;

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

int find(int s, int t) {

    int f = 0;

    while (1) {
        forn(i, N)
            used[i] = false;


        int df = dfs(s, inf, t);

        if (!df)
            break;

        f += df;
    }

    return f;
}

void add(int x, int y) {
    add(x * 2 + 1, y * 2, 1);
}

string A[57];
int n, m;

bool ok(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int solve() {
    cin >> n >> m;

    N = n * m * 2 + 7;

    E.resize(N);

    forn(i, n) {
        cin >> A[i];
    }

    forn(i, n) {
        forn(j, m) {
            if (A[i][j] == '.')
                continue;

            int t = i * m + j;

            const char * num = ".HONC";
            add(2 * t, 2 * t + 1, strchr(num, A[i][j]) - num); 

            if ((i + j) % 2 == 0)
                add(2 * n * m, 2 * t, 10);
            if ((i + j) % 2 == 1)
                add(2 * t + 1, 2 * n * m + 1, 10);
        }
    }

    forn(i, n) {
        forn(j, m) {
            if ((i + j) % 2)
                continue;

            if (A[i][j] == '.')
                continue;

            forn(gg, 4) {
                int ni = i + dx[gg], nj = j + dy[gg];

                if (ok(ni, nj) && A[ni][nj] != '.') {
                    add(i * m + j, ni * m + nj);
                }
            }
        }
    }

    find(2 * n * m, 2 * n * m + 1);

    bool ok = true;
    bool was = false;

    forn(i, n) {
        forn(j, m) {
            if (A[i][j] != '.')
                was = true;

            int t = i * m + j;

            for (auto &e : E[2 * t]) {
                if (e.to == 2 * t + 1 && e.f < e.c)
                    ok = false;
            }
        }
    }

    if (ok && was)
        puts("Valid");
    else
        puts("Invalid");

	return 0;
}