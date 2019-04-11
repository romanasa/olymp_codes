#include <bits/stdc++.h>

#define ll long long
#define db double

using namespace std;

struct pt{
    db x, y;
    pt operator- (pt nxt) const { return {x - nxt.x, y - nxt.y}; }
    pt operator+ (pt nxt) const { return {x + nxt.x, y + nxt.y}; }
    db len() { return sqrt(x * x + y * y); }
    void norm(db val) { db now = sqrt(x * x + y * y); x /= now / val, y /= now / val; }
};

db r;
pt a, b;

int main() {
    freopen("spy.in", "r", stdin);
    freopen("spy.out", "w", stdout);
    cin >> r >> a.x >> a.y >> b.x >> b.y;
    db vl = 0, vr = 1;
    pt tmp = b - a;
    db mi = r + 7;
    for (int it = 0; it < 200; it++){
        db vm1 = vl + (vr - vl) / 3;
        db vm2 = vr - (vr - vl) / 3;
        pt p1 = tmp, p2 = tmp;
        p1.norm(vm1 * (b - a).len());
        p2.norm(vm2 * (b - a).len());
        p1 = p1 + a;
        p2 = p2 + a;
        mi = min(mi, (p1 - pt{0, 0}).len());
        mi = min(mi, (p2 - pt{0, 0}).len());
        if ((p1 - pt{0, 0}).len() > (p2 - pt{0, 0}).len())
            vl = vm1;
        else
            vr = vm2;
    }
    //cout << mi << endl;
    if (mi < r)
        cout << "NO";
    else
        cout << "YES";
}
