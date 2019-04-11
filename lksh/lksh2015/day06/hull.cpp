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

#define TASK "hull"

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
    friend bool operator <(pt a, pt b) {
        if (a.y == b.y)
            return a.x < b.x;
        return a.y < b.y;
    }
};

struct vt {
    ll x, y;
    vt() {}
    vt(ll _x, ll _y) : x(_x), y(_y) {}
    vt(pt a, pt b) {
        x = b.x - a.x, y = b.y - a.y;
    }
    friend ll operator % (vt a, vt b) {
        return a.x * b.y - a.y * b.x;
    }
    ll dist() {
        return x * x + y * y;
    }
};

set<pt> s;

int solve() {
    int n;
    cin >> n;
    vector<pt> pent(n), p;
    forn(i, n) {
        cin >> pent[i].x >> pent[i].y;
        s.insert(pent[i]);
    }

    for (pt x : s)
        p.pk(x);
    pt minp = p[0];

    auto cmp = [minp](pt a, pt b) {
        if ((vt(minp, a) % vt(minp, b)) == 0)
            return (vt(minp, a).dist() < vt(minp, b).dist());
        return (vt(minp, a) % vt(minp, b)) > 0;
    };

    sort(all(p), cmp);

    vector<pt> st;
    for (int i = 0; i < p.size(); i++) {
        int en = st.size() - 1;
        while (st.size() > 1 && (vt(st[en - 1], st[en]) % vt(st[en], p[i])) <= 0) {
            en--;
            st.pop_back();
        }
        st.pk(p[i]);
    }

    cout << st.size() << "\n";
    for (pt a: st)
        cout << a.x << " " << a.y << "\n";
    return 0;
}