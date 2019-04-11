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

#define TASK "rendezvous"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int INF = (int)2e9 + 1;
const ll LINF = (ll)9e18 + 7;
const ll MM = (ll)1e9 + 7;

int solve();
void gen(int);

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

struct pt {
    ll x, y;
    int ind;
    pt() {}
    pt(ll _x, ll _y) : x(_x), y(_y) {}
};

struct answ {
    int a, b;
    ll d;
    answ() {}
    answ(ll _d, int _a, int _b) : d(_d), a(_a), b(_b) {}
    friend bool operator < (answ a, answ b) {
        return a.d < b.d;
    }
};

ll dist(pt a, pt b) {
    return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

vector<pt> p;

answ go(int l, int r) {
    if (r - l == 1)
        return answ(LINF, -1, -1);

    int m = (l + r) / 2;
    ll midx = p[m].x;
    answ ansl = go(l, m), ansr = go(m, r);
    answ cur_ans = min(ansl, ansr);
    ll h = cur_ans.d;

    vector<pt> res(r - l), cur;

    merge(p.begin() + l, p.begin() + m, p.begin() + m, p.begin() + r, 
        res.begin(), [](pt a, pt b) { return a.y == b.y ? a.x < b.x : a.y < b.y; });
    
    for (pt x : res)
        if (h > (midx - x.x) * (midx - x.x))
            cur.pk(x);
    
    answ ans(LINF, -1, -1);

    forn(i, cur.size()) {
        int j = i - 1;
        while (j >= 0 && (cur[i].y - cur[j].y) * (cur[i].y - cur[j].y) < h) {
            ans = min(ans, answ(dist(cur[i], cur[j]), cur[i].ind, cur[j].ind)), j--;
        }
    }

    for (int i = l; i < r; i++)
        p[i] = res[i - l];

    return min(cur_ans, ans);
}

int solve() {
    int n;
    cin >> n;
    p.resize(n);
    forn(i, n) {
        cin >> p[i].x >> p[i].y;
        p[i].ind = i;
    }
    ll ans2 = LINF;
    forn(i, n)
        forn(j, n)
            if (i != j)
                ans2 = min(ans2, dist(p[i], p[j]));

    vector<pt> old = p;
    sort(all(p), [](pt a, pt b) { return a.x == b.x ? a.y < b.y : a.x < b.x; });

    answ res = go(0, n);
    ll ans1 = dist(old[res.a], old[res.b]);
    cout << old[res.a].x << " " << old[res.a].y << "\n" << old[res.b].x << " " << old[res.b].y << "\n";

    return 0;
}