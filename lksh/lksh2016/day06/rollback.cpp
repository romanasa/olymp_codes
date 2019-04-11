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

#define TASK "rollback"

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

typedef struct node* pnode;

struct node {
    int val;
    pnode l, r;

    node() {}
    node(int val) : val(val), l(NULL), r(NULL) {}
    node(pnode l, pnode r) : l(l), r(r) {
        val = l->val + r->val;
    }
};

pnode build(pnode T, int tl, int tr, vector<int> &a) {
    if (T == NULL)
        T = new node(0);

    if (tl == tr) {
        return new node(a[tl]);
    } else {

        int tm = (tl + tr) / 2;
        return new node(build(T->l, tl, tm, a), build(T->r, tm + 1, tr, a));
    }
}

pnode upd(pnode T, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        return new node(val + T->val);
    }
    int tm = (tl + tr) / 2;

    if (pos <= tm) {
        return new node(upd(T->l, tl, tm, pos, val), T->r);
    } else {
        return new node(T->l, upd(T->r, tm + 1, tr, pos, val));
    }
}

int get(pnode T, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;

    if (tl == l && tr == r) {
        return T->val;
    }
    int tm = (tl + tr) / 2;

    if (r <= tm)
        return get(T->l, tl, tm, l, r);
    if (l > tm)
        return get(T->r, tm + 1, tr, l, r);

    return get(T->l, tl, tm, l, tm) + get(T->r, tm + 1, tr, tm + 1, r);
}

vector<pnode> T(1);

int solve() {
    int n, m;
    cin >> n >> m;

    vector<int> G(n + 1);

    T[0] = build(T[0], 0, n, G);

    map<int, int> M;

    forn(i, n) {
        int t;
        cin >> t;

        G[i] = M[t];
        M[t] = i + 1;
    }

    forn(i, n) {
        T.push_back(upd(T.back(), 0, n, G[i], 1));
    }

    int q;
    cin >> q;

    int p = 0;

    while (q--) {
        int x, y;
        cin >> x >> y;

        int l = ((x + p) % n) + 1;
        int k = ((y + p) % m) + 1;

        int L = l - 1, R = n;

        while (R - L > 1) {
            int M = (L + R) / 2;

            if (get(T[M], 0, n, 0, l - 1) - get(T[l - 1], 0, n, 0, l - 1) >= k)
                R = M;
            else
                L = M;
        }

        if (get(T[R], 0, n, 0, l - 1) - get(T[l - 1], 0, n, 0, l - 1) >= k) {
            cout << R << "\n";
            p = R;
        } else {
            cout << 0 << "\n";
            p = 0;
        }
    }

    return 0;
}