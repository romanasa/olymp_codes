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

#define TASK "rooks"

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
vector<ll> T(4 * MAXN);

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

void update(int v, int tl, int tr, int pos, int val) {
    if (tl == pos && tr == pos)
        T[v] = val;
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v * 2, tl, tm, pos, val);
        else if (pos <= tr)
            update(v * 2 + 1, tm + 1, tr, pos, val);
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

struct pt {
    ll x, y;
    pt() {}
    pt(ll _x, ll _y) : x(_x), y(_y) {}
};

struct req {
    int x1, y1, x2, y2, ind;
};

int solve() {
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    vector<pt> ls(k);
    vector<req> ps(q);

    forn(i, k) 
        cin >> ls[i].x >> ls[i].y;
    
    forn(i, q) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        
        ps[i].x1 = a, ps[i].x2 = c;
        ps[i].y1 = b, ps[i].y2 = d;
        
        ps[i].ind = i;
    }

    vector<bool> ok1(q, false), ok2(q, false);
    

    sort(all(ls), [](pt a, pt b){return a.x == b.x ? a.y < b.y : a.x < b.x; });
    sort(all(ps), [](req a, req b) {return a.x2 < b.x2; });

    int i = 0, j = 0;
    for (int x = 0; x <= 100000; x++) {
        while (i < ls.size() && ls[i].x == x)
            update(1, 0, 100000, ls[i].y, x), i++;

        while (j < ps.size() && ps[j].x2 == x) {
            int cur = get(1, 0, 100000, ps[j].y1, ps[j].y2);
            if (cur >= ps[j].x1)
                ok1[ps[j].ind] = true;
            j++;
        }
    }

    T.assign(4 * MAXN, 0);

    sort(all(ls), [](pt a, pt b){return a.y == b.y ? a.x < b.x : a.y < b.y; });
    sort(all(ps), [](req a, req b) {return a.y2 < b.y2; });

    i = 0, j = 0;
    for (int y = 0; y <= 100000; y++) {
        while (i < ls.size() && ls[i].y == y)
            update(1, 0, 100000, ls[i].x, y), i++;

        while (j < ps.size() && ps[j].y2 == y) {
            if (get(1, 0, 100000, ps[j].x1, ps[j].x2) >= ps[j].y1)
                ok2[ps[j].ind] = true;
            j++;
        }
    }

    forn(i, q)
        if (ok1[i] || ok2[i])
            cout << "YES\n";
        else
            cout << "NO\n";

    return 0;
}