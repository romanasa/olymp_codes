#include <bits/stdc++.h>
 
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
const int dd = 3007;
 
struct pt {
    ll x, y;
};
 
struct vt {
    ll x, y;
    vt(pt a, pt b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    ll dist() {
        return x * x + y * y;
    }
    ll operator % (vt b) {
        return x * b.y - y * b.x;
    }
};
 
vector<pt> T, R;
 
ll get(pt A, ll a, ll b) {
    return a * A.x + b * A.y;
}
 
const ll inf = (ll)1e18 + 7;
 
ll get(ll a, ll b) {
    ll ans = -inf;
    for (pt p : R)
        ans = max(ans, get(p, a, b));
         
    int l = 0, r = (int)T.size();
     
    ll j = get(T[0], a, b);
     
    while (r - l > 1) {
        int m = (l + r) / 2;
        int nxt = (m + 1) % (int)T.size();
         
        bool ok1 = get(T[m], a, b) >= j;
        bool ok2 = get(T[m], a, b) > get(T[nxt], a, b);
         
        ans = max(ans, get(T[m], a, b));
        ans = max(ans, get(T[nxt], a, b));
         
        if (ok1 && !ok2)
            l = m;
        else
            r = m;
    }
     
    l = 0, r = (int)T.size();
     
    while (r - l > 1) {
        int m = (l + r) / 2;
        int nxt = (m + 1) % (int)T.size();
         
        bool ok1 = (get(T[m], a, b)) >= (j);
        bool ok2 = (get(T[m], a, b)) > (get(T[nxt], a, b));
         
        ans = max(ans, get(T[m], a, b));
        ans = max(ans, get(T[nxt], a, b));
         
        if (ok1 && ok2)
            r = m;
        else
            l = m;
    }
     
    return ans;
}
 
void build() {
 
    while (T.size()) {
        R.push_back(T.back());
        T.pop_back();
    }
     
    if (R.size() == 0)
        return;
     
    sort(R.begin(), R.end(), [](pt a, pt b) {return a.x == b.x ? a.y < b.y : a.x < b.x;});
    pt O = R[0];
     
    sort(R.begin() + 1, R.end(), [O](pt A, pt B) {
        ll t = vt(O, A) % vt(O, B); 
        if (t == 0)
            return vt(O, A).dist() < vt(O, B).dist();
        return t > 0;
    });
     
    for (auto p : R) {
        while (T.size() > 1 && (vt(T[T.size() - 2], T.back()) % vt(T.back(), p) <= 0))
            T.pop_back();
        T.push_back(p);
    }
}
 
const int C = 3228;
 
int main() {
#ifndef HOME
    freopen("mostfar.in", "r", stdin);
    freopen("mostfar.out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
     
     
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        R.push_back({x, y});
    }
     
    build();
     
     
    int q;
    scanf("%d", &q);
     
    while (q--) {
        char a, b, c;
        scanf("\n%c%c%c", &a, &b, &c);
         
        int x, y;
        scanf("%d %d", &x, &y);
         
        if (a == 'g') {
            printf("%lld\n", get(x, y));
        } else {
            R.push_back({x, y});
        }
        if (R.size() > C) {
            build();
        }
    }
    return 0;
}