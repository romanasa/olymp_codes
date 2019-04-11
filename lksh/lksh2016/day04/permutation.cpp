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

#define TASK "permutation"

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

vector<int> T[4 * dd];

void build(int v, int tl, int tr, vector<int> &a) {
    T[v].resize(tr - tl + 1);

    if (tl == tr) {
        T[v][0] = a[tl];
    } else {
        int tm = (tl + tr) / 2;

        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm + 1, tr, a);

        merge(all(T[v * 2]), all(T[v * 2 + 1]), T[v].begin());
    }
}

int get(int v, int x, int y) {

    int indL = lower_bound(all(T[v]), x) - T[v].begin();
    int indR = upper_bound(all(T[v]), y) - T[v].begin();

    return indR - indL;
}

int get(int v, int tl, int tr, int l, int r, int x, int y) {
    if (l == tl && tr == r) {
        return get(v, x, y);
    }
    int tm = (tl + tr) / 2;
    if (r <= tm)
        return get(v * 2, tl, tm, l, r, x, y);
    if (l > tm)
        return get(v * 2 + 1, tm + 1, tr, l, r, x, y);

    return get(v * 2, tl, tm, l, tm, x, y) + get(v * 2 + 1, tm + 1, tr, tm + 1, r, x, y);
}

int solve() {
    int n, k;
    scanf("%d %d", &n, &k);

    vector<int> G(n);

    forn(i, n) {
        scanf("%d", &G[i]);
    }

    build(1, 0, n - 1, G);

    while (k--) {
        int x, y, l, r;
        scanf("%d %d %d %d", &l, &r, &x, &y);
        printf("%d\n", get(1, 0, n - 1, l - 1, r - 1, x, y));
    }
    return 0;
}