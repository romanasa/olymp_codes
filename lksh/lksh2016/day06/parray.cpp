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

#define TASK "parray"

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
    node(pnode l, pnode r, int x) : l(l), r(r) {
        val = l->val + r->val + x;
    }

    int get(int tl, int tr, int pos) {
        if (tl == tr) {
            return val;
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            return l->get(tl, tm, pos);
        } else if (pos <= tr) {
            return r->get(tm + 1, tr, pos);
        }
    }

    pnode upd(int tl, int tr, int pos, int val) {
        if (tl == tr) {
            return new node(val);
        }
        int tm = (tl + tr) / 2;

        if (pos <= tm) {
            return new node(l->upd(tl, tm, pos, val), r, val);
        } else {
            return new node(l, r->upd(tm + 1, tr, pos, val), val);
        }
    }
};

pnode build(pnode T, int tl, int tr, vector<int> &a) {
    if (T == NULL)
        T = new node(0);

    if (tl == tr) {
        return new node(a[tl]);
    } else {

        int tm = (tl + tr) / 2;
        return new node(build(T->l, tl, tm, a), build(T->r, tm + 1, tr, a), T->val);
    }
}

int solve() {
    int n;
    cin >> n;

    vector<pnode> T(1);
    vector<int> G(n);

    forn(i, n) {
        cin >> G[i];
    }

    T[0] = build(T[0], 0, n - 1, G);

    int m;
    cin >> m;

    while (m--) {
        string s;
        cin >> s;

        if (s == "get") {
            int i, j;
            cin >> i >> j;

            cout << T[i - 1]->get(0, n - 1, j - 1) << "\n";
        } else {
            int i, j, x;
            cin >> i >> j >> x;
            T.push_back(T[i - 1]->upd(0, n - 1, j - 1, x));
        }
    }

    return 0;
}