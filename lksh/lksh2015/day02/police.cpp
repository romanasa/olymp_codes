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
#include <tuple>

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

#define TASK "police"

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

int p[1007], cnt[1007];
int n, m, r;

int get(int v) {
    return v == p[v] ? v : p[v] = get(p[v]);
}

void un(int a, int b) {
    a = get(a);
    b = get(b);
    if (a != b) {
        if (cnt[a] < cnt[b])
            swap(a, b);
        p[b] = a, cnt[a] += cnt[b];
    }
}

int dx[] = { -1, 0, 0, 1 };
int dy[] = { 0, 1, -1, 0 };

bool ok(int i, int j) {
    return (i >= 0 && i < n && j >= 0 && j < m);
}

int solve() {
    cin >> n >> m >> r;
    vector<pair<int, int> > rs(r);
    vector<int> cost(r);
    forn(i, r) {
        cin >> rs[i].first >> rs[i].second >> cost[i];
        rs[i].first--, rs[i].second--;
    }

    vector<int> dist(n * m, INF), pr(n * m, -1), money(m * n);
    queue<int> q;
    forn(i, r) {
        dist[rs[i].first * m + rs[i].second] = 0, pr[rs[i].first * m + rs[i].second] = i;
        q.push(rs[i].first * m + rs[i].second);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        int i = v / m, j = v % m;
        forn(gg, 4) {
            int ni = i + dx[gg], nj = j + dy[gg];
            int nx = ni * m + nj;
            if (ok(ni, nj)) {
                if (dist[v] + 1 < dist[nx]) {
                    dist[nx] = dist[v] + 1, pr[nx] = pr[v];
                    q.push(nx);
                }
                if (pr[nx] != pr[v] && dist[v] + 1 == dist[nx])
                    pr[nx] = -2;
            }
        }
    }


    forn(x, n * m) 
        money[x] = (pr[x] != -2 ? cost[pr[x]] : INF);

    vector<tuple<int, int, int> > e;
    forn(x, n * m) {
        int i = x / m, j = x % m;
        if (money[x] != INF)
            e.pk(make_tuple(money[x], i, j));
    }

    sort(all(e));
    forn(i, n + m)
        p[i] = i, cnt[i] = 1;

    int res = 0;
    vector<pair<int, int> > ans;
    forn(i, e.size()) {
        int a, b, c;
        tie(c, a, b) = e[i];
        b += n;
        if (get(a) != get(b)) {
            res += c;
            ans.pk(mp(a, b));
            un(a, b);
        }
    }
    if (ans.size() != n + m - 1) {
        cout << -1;
        return 0;
    }
    cout << ans.size() << " " << res << "\n";
    forn(i, ans.size())
        cout << ans[i].first + 1 << " " << ans[i].second - n + 1 << "\n";
    return 0;
}