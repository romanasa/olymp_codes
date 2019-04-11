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

#define TASK "distinct"

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
typedef struct item* pitem;

struct item {
    ll val, add;
    pair<int, int> key;
    int prior;
    pitem l, r;

    item(pair<int, int> key, ll val, ll add): key(key), val(val), add(add), l(NULL), r(NULL) {
        prior = rand();
    }
};

ll getval(pitem T) {
    return T ? T->val : 0;
}

void upd(pitem &T) {
    if (!T)
        return;

    T->val = getval(T->l) + getval(T->r) + T->add;
}

void merge(pitem &T, pitem L, pitem R) {
    if (!L || !R) {
        T = L ? L : R;
        return;
    }

    if (L->prior > R->prior) {
        merge(L->r, L->r, R);
        T = L;
    } else {
        merge(R->l, L, R->l);
        T = R;
    }
    upd(T);
}

void split(pitem T, pitem &L, pitem &R, pair<int, int> key) {
    if (!T) {
        L = R = NULL;
        return;
    }

    if (key < T->key) {
        split(T->l, L, T->l, key);
        R = T;
    } else {
        split(T->r, T->r, R, key);
        L = T;
    }
    upd(L);
    upd(R);
    upd(T);
}

struct node {
    pitem T = NULL;

    void insert(pair<int, int> key, ll val) {
        pitem cur = new item(key, val, val);

        pitem L, R;

        split(T, L, R, key);

        merge(T, L, cur);
        merge(T, T, R);
    }

    void erase(pair<int, int> key) {
        pitem L, M, R;

        split(T, L, R, { key.first, key.second - 1 });
        split(R, M, R, key);

        merge(T, L, R);
    }

    ll get(int key) {
        pitem L, R;
        split(T, L, R, { key - 1, inf} );

        ll ans = 0;

        if (L) 
            ans = L->val;

        merge(T, L, R);

        return ans;
    }

} T[4 * dd];

ll get(int v, int tl, int tr, int l, int r, int x) {
    if (l == tl && tr == r) {
        return T[v].get(x);
    } else {
        int tm = (tl + tr) / 2;

        if (r <= tm)
            return get(v * 2, tl, tm, l, r, x);
        if (l > tm)
            return get(v * 2 + 1, tm + 1, tr, l, r, x);

        return get(v * 2, tl, tm, l, tm, x) + get(v * 2 + 1, tm + 1, tr, tm + 1, r, x);
    }
}

void upd(int v, int tl, int tr, int pos, int num, int old, int val) {
    if (tl != tr) {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            upd(v * 2, tl, tm, pos, num, old, val);
        else if (pos <= tr) 
            upd(v * 2 + 1, tm + 1, tr, pos, num, old, val);
    }

    T[v].erase({ old, pos });
    T[v].insert({ num, pos }, val);
}

void build(int v, int tl, int tr, vector<int> &a, vector<int> &b) {
    if (tl == tr) {
        T[v].insert({ a[tl], tl }, b[tl]);
    } else {
        int tm = (tl + tr) / 2;

        build(v * 2, tl, tm, a, b);
        build(v * 2 + 1, tm + 1, tr, a, b);

        for (int i = tl; i <= tr; i++)
            T[v].insert({ a[i], i }, b[i]);
    }
}

void print(pitem x) {
    if (!x)
        return;
    print(x->l);
    //cout << x->key << ", ";
    print(x->r);
}

map<int, set<int> > H;

int solve() {
    int n;
    scanf("%d", &n);

    vector<int> G(n), J(n);
    map<int, int> M;

    forn(i, n) {
        scanf("%d", &G[i]);

        H[G[i]].insert(i);

        if (M.count(G[i]))
            J[i] = M[G[i]];
        else
            J[i] = -1;
        M[G[i]] = i;
    }

    build(1, 0, n - 1, J, G);

    int q;
    scanf("%d", &q);

    while (q--) {
        char c;
        int l, r;
        scanf("\n%c %d %d", &c, &l, &r);

        if (c == 'Q') {
            printf("%lld\n", get(1, 0, n - 1, l - 1, r - 1, l - 1));
        } else {
            l--;
            int old = G[l];
            int ind = J[l];

            auto it = H[old].lower_bound(l);
            if (it != (--H[old].end())) {
                auto nxt = it;
                ++nxt;

                upd(1, 0, n - 1, *nxt, ind, J[*nxt], G[*nxt]);
                J[*nxt] = ind;
            }

            H[old].erase(l);
            H[r].insert(l);

            it = H[r].lower_bound(l);

            auto nxt = it;
            ++nxt;

            if (nxt != H[r].end()) {
                upd(1, 0, n - 1, *nxt, l, J[*nxt], G[*nxt]);
                J[*nxt] = l;
            }

            int newval = -1;
            if (it != H[r].begin()) {
                auto prev = it;
                prev--;

                newval = *prev;
            }


            G[l] = r;
            upd(1, 0, n - 1, l, newval, J[l], G[l]);
            J[l] = newval;
        }
    }
    return 0;
}