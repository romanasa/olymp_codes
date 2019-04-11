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
#include <unordered_set>
#include <cstring>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (ll i = 0; i < (ll)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "distinctnum"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int inf = (int)2e9 + 1;
const ll linf = (ll)9e18 + 7;
const ll MM = (ll)1e9 + 7;

int solve();

int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

const int MAXN = 3e5 + 7;
vector<int> T[4 * MAXN];

void build(int v, int tl, int tr, vector<int> &a) {
    if (tl == tr)
        T[v].pk(a[tl]);
    else {
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm + 1, tr, a);
        T[v].resize(tr - tl + 1);
        merge(T[v * 2].begin(), T[v * 2].end(), T[v * 2 + 1].begin(), T[v * 2 + 1].end(), T[v].begin());
    }
}

int get(int v, int tl, int tr, int l, int r, int k) {
    if (tl == l && tr == r) {
        return (lower_bound(T[v].begin(), T[v].end(), k) - T[v].begin());
    }
    else {
        int tm = (tl + tr) / 2;
        if (r <= tm)
            return get(v * 2, tl, tm, l, r, k);
        if (l > tm)
            return get(v * 2 + 1, tm + 1, tr, l, r, k);
        return get(v * 2, tl, tm, l, tm, k) + get(v * 2 + 1, tm + 1, tr, tm + 1, r, k);
    }
}

map<int, int> m;

int solve() {
    int n, q;
    cin >> n;
    vector<int> a(n), eq(n);

    forn(i, n)
        scanf("%d", &a[i]);

    vector<pair<int, int> > st;
    forn(i, n) {    
        if (m.count(a[i]))
            eq[i] = m[a[i]];
        else
            eq[i] = -1;
        m[a[i]] = i;
    }
    build(1, 0, n - 1, eq);

    cin >> q;
    forn(i, q) {
        int a, b;
        scanf("%d %d", &a, &b);
        int ans = get(1, 0, n - 1, a - 1, b - 1, a - 1);
        printf("%d\n", ans);
    }
    return 0;
}