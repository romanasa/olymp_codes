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

#define TASK "secure"

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

int type[5007], par[5007];
vector<vector<pair<int, ll> > > e(5007);

int solve() {
    int n, m;
    cin >> n >> m;
    forn(i, n) 
        cin >> type[i];
    forn(i, m) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        a--, b--;
        e[a].pk(mp(b, c));
        e[b].pk(mp(a, c));
    }

    vector<ll> dist(5007, INF);
    set<pair<ll, int> > s;
    forn(i, n)
        if (type[i] == 1) {
            dist[i] = 0, par[i] = i;
            s.insert(mp(dist[i], i));
        }

    while (!s.empty()) {
        int v = s.begin()->second;
        s.erase(s.begin());
        forn(i, e[v].size()) {
            int to = e[v][i].first, cost = e[v][i].second;
            if (dist[v] + cost < dist[to]) {
                dist[to] = dist[v] + cost, par[to] = par[v];
                s.insert(mp(dist[to], to));
            }
        }
    }
    int ind = -1;
    forn(i, n)
        if (type[i] == 2 && (ind == -1 || dist[i] < dist[ind]))
            ind = i;
    if (ind == -1 || dist[ind] == INF)
        cout << -1;
    else
        cout << par[ind] + 1 << " " << ind + 1 << " " << dist[ind];
    return 0;
}