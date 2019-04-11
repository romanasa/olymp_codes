#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

#define db long double
#include <cmath>
const db pi = atan2(1.0, 1.0) * 4;

struct pt{
    db x, y;
    pt() {}
    pt(db x1, db y1) { x = x1; y = y1; }
    pt operator- (pt nxt) const { return pt(x - nxt.x, y - nxt.y); }
    pt operator+ (pt nxt) const { return pt(x + nxt.x, y + nxt.y); }
    db len() { return sqrtl(x * x + y * y); }
    db squareLen() { return (x * x + y * y); }
    pt norm(db val) { db tmp = pt(x, y).len(); return pt(x * val / tmp, y * val / tmp); }
    pt rotate(db val) { return pt(x * cosl(val) - y * sinl(val), y * cosl(val) + x * sinl(val)); }
    db operator% (pt nxt) const { return x * nxt.y - y * nxt.x; }
    db operator* (pt nxt) const { return x * nxt.x + y * nxt.y; }
};

db R, rSmall, rBig;
pt s, t;

db getS(pt a, pt b, pt c){
    return abs((b - a) % (c - a)) / (db)2;
}

db getFunc(pt a, pt b, pt c, db r){
    db val = ((a - c) * (b - c)) / (a - c).len() / (b - c).len();
    //cout << "---" << val << ' ' << acos(val) * 180.0 / pi << endl;
    return acosl(val) * r * r / (db)2 - getS(a, b, c);
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    cin >> R >> rSmall >> rBig >> t.x >> t.y;
    s = pt(0, 0);
    db x = rSmall * (s - t).len() / (rBig - rSmall);
    pt v = (s - t).norm(x);
    pt g = s + v;
    db w = sqrtl(max((db)0, (t - g).squareLen() - rBig * rBig));
    pt tmp = t - s;

    pt p1 = tmp.rotate(asinl((rBig - rSmall) / (s - t).len()));
    pt p2 = tmp.rotate(-asinl((rBig - rSmall) / (s - t).len()));
    pt pw1 = g + p1.norm(w);
    pt pw2 = g + p2.norm(w);

    //cout << pw1.x << ' ' << pw1.y << ' ' << pw2.x << ' ' << pw2.y << endl;

    db ans = getS(g, pw1, pw2) - getFunc(pw1, pw2, t, rBig);

    db vl = 0, vr = 100000;
    for (int it = 0; it < 400; it++){
        db vm = (vl + vr) / (db)2;
        pt now = g + p1.norm(vm);
        if (now.squareLen() <= R * R)
            vl = vm;
        else
            vr = vm;
    }
    p1 = p1.norm(vl);

    vl = 0, vr = 100000;
    for (int it = 0; it < 400; it++){
        db vm = (vl + vr) / (db)2;
        pt now = g + p2.norm(vm);
        if (now.squareLen() <= R * R)
            vl = vm;
        else
            vr = vm;
    }
    p2 = p2.norm(vl);

    p1 = p1 + g;
    p2 = p2 + g;

    //cout << endl << p1.x << ' ' << p1.y << ' ' << p2.x << ' ' << p2.y << endl;

    ans = getS(g, p1, p2) - ans + getFunc(p1, p2, s, R);

    cout.precision(10);
    cout << fixed << (double)(100 * ans / (pi * R * R)) << endl;
    //cout << p1.x << ' ' << p1.y << ' ' << p2.x << ' ' << p2.y << endl;
}

