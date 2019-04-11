#define _CRT_SECURE_NO_WARNINGS
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

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "hull"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll inf = (ll)2e9 + 1;
const ll linf = (ll)8e18;

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

struct pt {
    ll x, y;
    bool operator < (pt b) const {
        return x == b.x ? y < b.y : x < b.x;
    }
};

struct vt {
    ll x, y;
    vt() {}
    vt(pt a, pt b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    ll operator % (vt b) {
        return x * b.y - y * b.x;
    }
};

ll dist(pt A, pt B) {
    return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y);
}

int solve() {
    int n;
    cin >> n;

    vector<pt> P(n);

    forn(i, n) {
        cin >> P[i].x >> P[i].y;
    }

    sort(all(P));
    
    pt O = P[0];

    sort(P.begin() + 1, P.end(), [O](pt A, pt B) {
        if (vt(O, A) % vt(O, B) == 0)
            return dist(O, A) < dist(O, B);
        return vt(O, A) % vt(O, B) > 0;
    });

    vector<pt> T;

    for (auto p : P) {
        while (T.size() > 1 && (vt(T[T.size() - 2], T.back()) % vt(T.back(), p) <= 0))
            T.pop_back();
        T.push_back(p);
    }

    cout << T.size() << "\n";
    for (auto p : T)
        cout << p.x << " " << p.y << "\n";
    return 0;
}