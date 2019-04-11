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

#define forn(i, n) for (ll i = 0; i < (ll)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "permutation"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int INF = (int)2e9 + 1;
const ll LINF = (ll)9e18 + 7;
const ll MM = (ll)1e9 + 7;

int solve();

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

const int MAXN = 1e5 + 7;

ll T[4 * MAXN];

void update(int v, int tl, int tr, int pos) {
    if (tl == pos && pos == tr) {
        T[v]++;
    }
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v * 2, tl, tm, pos);
        else if (pos <= tr)
            update(v * 2 + 1, tm + 1, tr, pos);

        T[v] = T[v * 2] + T[v * 2 + 1];
    }
}

ll get(int v, int tl, int tr, int l, int r) {
    if (l == tl && r == tr)
        return T[v];

    int tm = (tl + tr) / 2;

    if (r <= tm)
        return get(v * 2, tl, tm, l, r);
    if (l > tm)
        return get(v * 2 + 1, tm + 1, tr, l, r);

    return get(v * 2, tl, tm, l, tm) +
        get(v * 2 + 1, tm + 1, tr, tm + 1, r);
}

struct req {
    int x, l, r, op, ind;
    req() {}
    req(int _x, int _l, int _r, int _op, int _ind) : x(_x), l(_l), r(_r), op(_op), ind(_ind) {}
    friend bool operator <(req a, req b) {
        if (a.x == b.x)
            return (a.op > b.op);
        return a.x < b.x;
    }
};

int solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), ans(m);   
    vector<req> b;
    fornn(i, 1, n + 1)
        cin >> a[i];
    forn(i, m) {
        int x, y, l, r;
        cin >> x >> y >> l >> r;
        b.pk(req(x, l, r, 1, i));
        b.pk(req(y, l, r, 0, i));
    }
    sort(all(b));
    int j = 0;
    fornn(i, 1, n + 1) {
        while (j < b.size() && b[j].x == i && b[j].op)
            ans[b[j].ind] -= get(1, 0, n - 1, b[j].l, b[j].r), j++;
        update(1, 0, n - 1, a[i]);
        while (j < b.size() && b[j].x == i && !b[j].op)
            ans[b[j].ind] += get(1, 0, n - 1, b[j].l, b[j].r), j++;
    }
    forn(i, m)
        cout << ans[i] << "\n";
    return 0;
}