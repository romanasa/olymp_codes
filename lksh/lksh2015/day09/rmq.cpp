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

#define TASK "rmq"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int INF = (int)2e9 + 1;
const ll LINF = (ll)9e18 + 7;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

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

typedef struct item * pitem;

struct item {
    pitem l, r;
    ll y, val, cnt, ans;
    item() {}
    item(ll x) {
        ans = val = x;
        cnt = 1;
        y = rand();
        l = r = NULL;
    }
};

int cnt(pitem x) {
    return x ? x->cnt : 0;
}

ll ans(pitem x) {
    return x ? x->ans : INF;
}

void upd(pitem x) {
    if (!x)
        return;
    x->cnt = cnt(x->l) + cnt(x->r) + 1;
    x->ans = min(min(ans(x->l), ans(x->r)), x->val);
}

void split(pitem t, pitem &l, pitem &r, int key, int add = 0) {
    if (!t) 
        l = r = NULL;
    else {
        int cur = cnt(t->l) + add;
        if (cur <= key) 
            split(t->r, t->r, r, key, add + cnt(t->l) + 1), l = t;
        else
            split(t->l, l, t->l, key, add), r = t;
        upd(l);
        upd(r);
    }
}

void merge(pitem &t, pitem l, pitem r) {
    if (!l) {
        t = r;
        return;
    }
    if (!r) {
        t = l;
        return;
    }

    if (l->y > r->y) 
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    upd(t);
}

void print(pitem T) {
    if (!T)
        return;
    print(T->l);
    cout << T->val << " ";
    print(T->r);
}

int solve() {
    srand(135);
    
    pitem T = NULL;

    int m;
    cin >> m;
    forn(i, m) {
        char c; 
        cin >> c;
        if (c == '+') {
            int pos, val;
            cin >> pos >> val;
            pitem L, R, M = new item(val);
            split(T, L, R, pos - 1);
            merge(T, L, M), merge(T, T, R);
        }
        else {
            int l, r;
            cin >> l >> r;
            pitem L, R, M;
            split(T, L, R, r - 1);
            split(L, L, M, l - 2);
            /*print(L); cout << "\n";
            print(M); cout << "\n";
            print(R); cout << "\n";*/
            cout << ans(M) << "\n";
            merge(T, L, M), merge(T, T, R);
        }
        //print(T); cout << "\n\n";
    }
    return 0;
}