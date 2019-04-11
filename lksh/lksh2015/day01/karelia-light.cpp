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

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (int i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "karelia-light"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int INF = (int)2e9 + 1;
const ll LINF = (ll)8e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

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
    pt() {}
    pt(ll _x, ll _y) : x(_x), y(_y) {}
};

struct vt {
    ll x, y;
    vt(ll _x, ll _y) : x(_x), y(_y) {}
    vt(pt a, pt b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    friend ll operator %(vt a, vt b) {
        return a.x * b.y - a.y * b.x;
    }
    friend bool operator <(vt a, vt b) {
        return (a % b) > 0;
    }
};

int ans[15];
pt start;

bool cmp(pt a, pt b) {
    return vt(start, a) < vt(start, b);
}

int solve() {
    int n, l;
    cin >> n >> l;
    vector<pt> allp(n + 1);
    forn(i, n)
        cin >> allp[i].x >> allp[i].y;

    forn(msk, (1 << n)) {
        int cur = 0;
        vector<pt> p;
        forn(i, n)
            if (msk & (1 << i))
                cur++, p.pk(allp[i]);

        if (cur < 3 || cur > n)
            continue;

        bool ok = true;
        int ind = 0;
        forn(i, p.size())
            if (p[i].x < p[ind].x || p[i].x == p[ind].x && p[i].y < p[ind].y)
                ind = i;
        swap(p[0], p[ind]);
        start = p[0];
        sort(p.begin() + 1, p.end(), cmp);
        p.pk(p[0]);
        p.pk(p[1]);
        bool ok1 = true, ok2 = true;
        fornn(i, 1, p.size() - 1) {
            if (vt(p[i - 1], p[i]) % vt(p[i], p[i + 1]) > 0)
                ok1 = false;
            if (vt(p[i - 1], p[i]) % vt(p[i], p[i + 1]) < 0)
                ok2 = false;
        }
        if (ok1 || ok2)
            ans[cur]++;
    }
    forn(i, l) {
        int v;
        cin >> v;
        cout << ans[v] << " ";
    }
    return 0;
}