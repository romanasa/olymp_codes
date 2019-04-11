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

struct req {
    ll l, q, op;
    req() {}
    req(ll _l, ll _q, ll _op) : l(_l), q(_q), op(_op) {}
};

const int MAXN = 1e5 + 7;
vector<ll> T(4 * MAXN, LINF);

void buildt(int v, int tl, int tr, vector<ll> &a) {
    if (tl == tr)
        T[v] = a[tl];
    else {
        int tm = (tl + tr) / 2;
        buildt(v * 2, tl, tm, a);
        buildt(v * 2 + 1, tm + 1, tr, a);

        T[v] = min(T[v * 2], T[v * 2 + 1]);
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
    
    return min(get(v * 2, tl, tm, l, tm), 
        get(v * 2 + 1, tm + 1, tr, tm + 1, r));
}

int solve() {
    int n, m;
    cin >> n >> m;
    vector<req> a;
    vector<ll> l(m), r(m), q(m);

    forn(i, m) {
        cin >> l[i] >> r[i] >> q[i];
        l[i]--, r[i]--;
        a.pk(req(l[i], q[i], 1));
        a.pk(req(r[i], q[i], 0));
    }

    sort(all(a), [](req a, req b){return a.l == b.l ? a.op > b.op : a.l < b.l;});

    multiset<ll> s;
    vector<ll> ans(n);
    int j = 0;
    forn(i, n) {
        while (j < a.size() && a[j].l == i && a[j].op)
            s.insert(a[j].q), j++;

        if (s.size())
            ans[i] = *s.rbegin();

        while (j < a.size() && a[j].l == i && !a[j].op)
            s.erase(s.find(a[j].q)), j++;
    }

    bool ok = true;
    buildt(1, 0, n - 1, ans);
    forn(i, m)
        if (get(1, 0, n - 1, l[i], r[i]) != q[i])
            ok = false;

    if (ok) {
        cout << "consistent\n";
        forn(i, n) 
            cout << ans[i] << " ";
    }
    else
        cout << "inconsistent\n";

    return 0;
}