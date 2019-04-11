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

#define TASK "dominoes"

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

vector<vector<int> > e;

char f[107][107];

int n, m;
int dx[] = {-1, 0,  0, 1};
int dy[] = { 0, 1, -1, 0};

bool ok(int i, int j) {
    return (i >= 0 && i < n && j >= 0 && j < m);
}

void add(int i, int j, int ni, int nj) {
    e[i * m + j].pk(ni * m + nj);
}

int pr[20007], used[20007];
int tmm = 1;

bool dfs(int v) {
    if (used[v] == tmm) return false;
    used[v] = tmm;
    forn(i, e[v].size()) {
        int to = e[v][i];
        if (pr[to] == -1 || dfs(pr[to])) {
            pr[to] = v;
            return true;
        }
    }
    return false;
}

int solve() {
    int a, b, res = 0;
    cin >> n >> m >> a >> b;
    e.resize(n * m);
    forn(i, n)
        forn(j, m) {
            cin >> f[i][j];
            res += (f[i][j] == '*');
        }
    if (a >= 2 * b) {
        cout << b * res;
    }
    else {
        forn(i, n)
            forn(j, m) {
                if ((i + j) % 2)
                    continue;
                forn(gg, 4) {
                    int ni = i + dx[gg], nj = j + dy[gg];
                    if (ok(ni, nj) && f[i][j] == '*' && f[ni][nj] == '*')
                        add(i, j, ni, nj);
                }
            }
        forn(x, n * m)
            pr[x] = -1;

        forn(x, n * m) {
            tmm++;
            dfs(x);
        }

        int ans = 0;
        forn(x, n * m)
            ans += (pr[x] != -1);
        cout << (ll)ans * (ll)a + (ll)(res - ans * 2) * (ll)b;
    }
    return 0;
}