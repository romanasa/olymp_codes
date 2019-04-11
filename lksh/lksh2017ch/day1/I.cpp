#include <bits/stdc++.h>

using namespace std;

#define ld double
#define mp make_pair
#define x first
#define y second

struct pt{
    ld x, y;
    pt() {}
    pt(ld x1, ld y1) { x = x1, y = y1; }
    ld operator% (pt nxt) const { return x * nxt.y - y * nxt.x; }
    pt operator- (pt nxt) const { return pt(x - nxt.x, y - nxt.y); }
};

ld getDistPointPoint(pt a, pt b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

ld getDoubleSquareTriangle(pt a, pt c, pt d){
    return abs((c - a) % (d - a));
}

ld getDistPointLine(pt a, pt c, pt d){
    return getDoubleSquareTriangle(a, c, d) / getDistPointPoint(c, d);
}

pair<pair<ld, ld>, ld> getLine(pt s, pt t){
    ld a = t.y - s.y;
    ld b = s.x - t.x;
    ld c = s.y * (t.x - s.x) - s.x * (t.y - s.y);
    return mp(mp(a, b), c);
}

ld getSign(ld val){
    if (val < 0) return -1;
    if (val > 0) return 1;
    return 0;
}

ld getSignDist(pt a, pt b){
    auto now = getLine(a, b);
    return getSign(now.y);
}

ld getMyFunc(ld xx, pair<pair<ld, ld>, ld> s, pt c, pt d){
    pt w = pt(xx, (-s.y - s.x.x * xx) / s.x.y);
    return getDistPointPoint(pt(0, 0), w) + getDistPointLine(w, c, d);
}

ld getFunc(pt a, pt b, pt c, pt d){
    if (((a - b) % (c - d)) == 0){
        ld val1 = getDistPointLine(pt(0, 0), a, b);
        ld val2 = getDistPointLine(pt(0, 0), c, d);
        //cout << a.x << ' ' << a.y << ' ' << b.x << ' ' << b.y << ' ' << c.x << ' ' << c.y << ' ' << d.x << ' ' << d.y << endl;
        if (getSignDist(a, b) != getSignDist(c, d)) return min(val1, val2) * (ld)2 + max(val1, val2);
        return max(val1, val2);
    }
    if (a.x == b.x){
        swap(a, c);
        swap(b, d);
    }
    auto s = getLine(a, b);
    auto t = getLine(c, d);
    ld vl = -1e8, vr = 1e8;
    for (int it = 0; it < 200; it++){
        double f1 = vl + (vr - vl) / 3;
        double f2 = vr - (vr - vl) / 3;
        if (getMyFunc(f1, s, c, d) > getMyFunc(f2, s, c, d))
            vl = f1;
        else
            vr = f2;
    }
    return getMyFunc(vl, s, c, d);
}

pt a[4];

int main() {
    //freopen("01.in", "r", stdin);
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
    ld ans = 1e9;
    for (int i = 0; i < 4; i++){
        int xx, yy;
        cin >> xx >> yy;
        a[i] = pt(xx, yy);
    }
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) for (int s = 0; s < 4; s++) for (int f = 0; f < 4; f++){
        set<int> se;
        se.insert(i), se.insert(j), se.insert(s), se.insert(f);
        if (se.size() == 4){
            ans = min(ans, getFunc(a[i], a[j], a[s], a[f]));
        }
    }
    cout.precision(10);
    cout << fixed << (double)ans;
}
