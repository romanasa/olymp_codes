#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define all(x) (x).begin(), (x).end()
//#define int ll

void FAST_IO() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.setf(ios::fixed);
    cout.precision(20);
}

struct point {
    ll x, y;
    point() : x(0), y(0) {};
    point(ll a, ll b) : x(a), y(b) {};

    bool operator ==(const point &other) const {
        return x == other.x && y == other.y;
    }

    friend istream& operator >>(istream& in, point &p) {
        in >> p.x >> p.y;
        return in;
    }

    friend ostream& operator <<(ostream& out, point &p) {
        out << p.x << ' ' << p.y;
        return out;
    }

};

struct vect {
    ll x, y;
    vect() : x(0), y(0) {};
    vect(ll a, ll b) : x(a), y(b) {};
    vect(point a, point b) : x(b.x - a.x), y(b.y - a.y) {};

    ll operator *(const vect &other) const  {
        return x * other.x + y * other.y;
    }

    ll operator ^(const vect &other) const  {
        return x * other.y - y * other.x;
    }
};

ll sign(ll a) {
    return (a > 0 ? 1 : a < 0 ? -1 : 0);
}

inline ll dist(point a, point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

mt19937 gen(time(0));
const int MAXN = 1e5 + 100;
point p[MAXN], s[MAXN];
int sz = 1;

bool cmp(point a, point b) {
    ll res = vect(p[0], a) ^ vect(a, b);
    return res > 0 || res == 0 && dist(p[0], a) < dist(p[0], b);
}

signed main() {
    FAST_IO();
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    int v = 0;
    for (int i = 1; i < n; ++i) {
        if (p[i].y < p[v].y || p[i].y == p[v].y && p[i].x > p[v].x) {
            v = i;
        }
    }
    swap(p[0], p[v]);
    sort(p + 1, p + n, cmp);
    s[0] = p[0];
    for (int i = 1; i < n; ++i) {
        while (sz > 1) {
            if ((vect(s[sz - 2], s[sz - 1]) ^ vect(s[sz - 1], p[i])) <= 0) {
                sz--;
            }
            else {
                s[sz++] = p[i];
                break;
            }
        }
        if (sz == 1) {
            s[sz++] = p[i];
        }
    }
    n = sz;
    ll ans = 0;
    while (clock() / 1. / CLOCKS_PER_SEC < 0.99) {
        int l = gen() % n;
        int r = gen() % n;
        for (int i = max(-200, -n); i <= min(200, n); ++i) {
            for (int j = max(-200, -n); j <= min(200, n); ++j) {
                int new_l = (l + i + n + n) % n;
                int new_r = (r + i + n + n) % n;
                ans = max(ans, dist(s[new_l], s[new_r]));
            }
        }
    }
    cout << sqrt(ans);
}