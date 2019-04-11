#include <bits/stdc++.h>

#define MOD (1000000007)
#define EPS (1e-9)
#define INF (2117117117)
#define LLINF (2117117117117117117LL)
#define mp(a, b) make_pair(a, b)
#define pb(a) push_back(a)
#define sqr(a) ((a) * (a))
#define sz(a) ((int) (a).size())

typedef unsigned int uint;
typedef long long llong;
typedef long double ldouble;
typedef unsigned long long ullong;

using namespace std;

#define TASK "upsolving"

const int MAXN = 200117, MAXL = 19;

int n, l[MAXN], ct[MAXN][MAXL], pos[MAXN][MAXL], d[MAXN][MAXL], a, b, s[MAXN];
vector<int> g[MAXN], pm[MAXN];

void calc_s(int v, int par = -1)
{
    s[v] = 1;
    for (auto u : g[v])
        if (u != par && l[u] == -1)
            calc_s(u, v), s[v] += s[u];
}

int find_centroid(int v, int cur_n, int par = -1)
{
    for (auto u : g[v])
        if (u != par && l[u] == -1 && 2 * s[u] >= cur_n)
            return find_centroid(u, cur_n, v);
    return v;
}

void dfs(int v, int lvl, int depth, int ctr, int par = -1)
{
    ct[v][lvl] = ctr;
    d[v][lvl] = depth;
    for (auto u : g[v])
        if (u != par && l[u] == -1)
            dfs(u, lvl, depth + 1, ctr, v);
}

void build(int v, int lvl)
{
    calc_s(v);
    v = find_centroid(v, s[v]);
    l[v] = lvl;
    dfs(v, lvl, 0, v);
    for (auto u : g[v])
        if (l[u] == -1)
            build(u, lvl + 1);
}

inline int get(int v)
{
    int res = INF;
    for (int i = 0; i <= l[v]; i++)
        if (pos[v][i] != sz(pm[ct[v][i]]) &&
                res > pm[ct[v][i]][pos[v][i]] + d[v][i])
            res = pm[ct[v][i]][pos[v][i]] + d[v][i];
    return res;
}

int main()
{
    freopen(TASK ".in", "r", stdin);
    freopen(TASK ".out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d %d", &a, &b);
        a--, b--;
        g[a].pb(b);
        g[b].pb(a);
    }
    fill(l, l + n, -1);
    build(0, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= l[i]; j++)
            pm[ct[i][j]].pb(d[i][j]), pos[i][j] = sz(pm[ct[i][j]]);
    for (int i = 0; i < n; i++)
        for (int j = sz(pm[i]) - 2; j >= 0; j--)
            if (pm[i][j + 1] < pm[i][j])
                pm[i][j] = pm[i][j + 1];
    for (int i = 0; i < n - 1; i++)
        printf("%d\n", get(i));
    
    return 0;
}
