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

#define TASK "battleship"

const double eps = 1e-3;
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

struct pt {
    ll x, y;
    pt() {}
    pt(ll _x, ll _y) : x(_x), y(_y) {}
};

double get(double x, double y, vector<pt> &cur) {
    double ans = 0;
    for (pt a : cur) {
        ans = max(ans, (x - a.x) * (x - a.x) + (y - a.y) * (y - a.y));
    }
    return ans;
}

double f(double x, vector<pt> &cur) {
    double ly = -10007, ry = 10007;
    while (ry - ly > eps) {
        double m1 = ly + (ry - ly) / 3,
            m2 = ry - (ry - ly) / 3;
        if (get(x, m1, cur) < get(x, m2, cur))
            ry = m2;
        else
            ly = m1;
    }
    return get(x, ly, cur);
}

bool ok(int msk) {
    double lx = 10007, rx = -10007;

    while (rx - lx > eps) {
        double m1 = lx + (rx - lx) / 3,
            m2 = rx - (rx - lx) / 3;
        if (f(m1, cur) < f(m2, cur))
            rx = m2;
        else
            lx = m1;
    }

    double ly = -100007, ry = 100007;
    while (ry - ly > eps) {
        double m1 = ly + (ry - ly) / 3,
            m2 = ry - (ry - ly) / 3;
        if (get(lx, m1, cur) < get(lx, m2, cur))
            ry = m2;
        else
            ly = m1;
    }

    printf("%.10f %.10f\n", lx, ly);
}

int solve() {
    cin >> n >> R;
    p.resize(n);
    forn(i, n)
        cin >> p[i].x >> p[i].y;

    forn(msk, 1 << n)
        dp[msk] = INF;

    dp[0] = 0;

    fornn(msk, 1, 1 << n) {
        if (ok(msk))
            dp[msk] = 1;
        else {
            for(int pdk = msk; pdk > 0; pdk = (pdk - 1) & msk) {
                int dop = msk - pdk;
                dp[msk] = min(dp[msk], dp[pdk] + dp[dop]);
            }
        }
    }

    cout << dp[(1 << n) - 1];

    return 0;
}