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

#define TASK "kalivech"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int INF = (int)2e9 + 1;
const ll LINF = (ll)9e18 + 7;
const ll MM = (ll)1e9 + 7;

int solve();

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

struct ls {
    ll y, tp, ind;
    ls() {}
    ls(ll _y, ll _tp, ll _ind) : y(_y), tp(_tp), ind(_ind) {}
    bool operator < (ls b) const {
        return y < b.y;
    }
};

struct req {
    ll x1, y1, y2, ind, tp;
    friend bool operator <(req a, req b) {
        if (a.x1 == b.x1) {
            if (a.tp == b.tp) {
                if (a.y1 == b.y1) 
                    return a.y2 < b.y2;
                return a.y1 < b.y1;
            }
            return a.tp < b.tp;
        }
        return a.x1 < b.x1;
    }
};

multiset<ls> s;

int solve() {
    ll n, w, h;
    cin >> n;
    cin >> w >> h;
    s.insert(ls(h, 0, n));

    vector<req> ss(2 * n);
    vector<ll> ans(n + 1), par(n + 1);

    forn(i, n) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);
        ss[2 * i].x1 = x1, ss[2 * i].y1 = y1, ss[2 * i].y2 = y2, ss[2 * i].ind = i, ss[2 * i].tp = 1;
        ss[2 * i + 1].x1 = x2, ss[2 * i + 1].y1 = y1, ss[2 * i + 1].y2 = y2, ss[2 * i + 1].ind = i, ss[2 * i + 1].tp = 0;
        ans[i] = (y2 - y1) * (x2 - x1);
    }

    ans[n] = w * h;

    sort(all(ss));

    forn(i, ss.size()) {

        ls cur1, cur2;
        cur1.y = ss[i].y1, cur2.y = ss[i].y2;
        cur1.tp = 1, cur2.tp = 0;
        cur1.ind = ss[i].ind, cur2.ind = ss[i].ind;

        if (ss[i].tp) {
            auto it = s.upper_bound(cur2);

            if (it->tp == 0)
                ans[it->ind] -= ans[ss[i].ind], par[ss[i].ind] = it->ind;
            if (it->tp == 1)
                ans[par[it->ind]] -= ans[ss[i].ind], par[ss[i].ind] = par[it->ind];

            s.insert(cur1), s.insert(cur2);
        }
        else
            s.erase(s.find(cur1)), s.erase(s.find(cur2));
    }
    sort(all(ans));
    forn(i, n + 1)
        cout << ans[i] << " ";
    return 0;
}