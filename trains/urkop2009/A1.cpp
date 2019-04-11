#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define db double

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

pt s, t;
db R, r1, r2;

pair<db, db> getalphax() {
    db r = r2 - r1;
    db x = (t - s).len();
    db alpha = asinl(r / x);
    return { alpha, sqrtl(x * x - r * r) };
}

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

    s = pt(0, 0);
    cin >> R >> r1 >> r2;
    cin >> t.x >> t.y;

    //cout << t.x << " " << t.y << "\n";

    auto c = getalphax();
    pt cur1 = t - s;
    pt cur2 = t - s;

    //cout << cur1.x << " " << cur1.y << " " << cur2.x << " " << cur2.y << "\n";

    cur1 = (cur1.norm(c.second)).rotate(c.first);
    cur2 = (cur2.norm(c.second)).rotate(-c.first);


    pt p1 = s + cur1;
    pt p2 = s + cur2;


    pt w1 = (p1 - t);
    pt w2 = (p2 - t);

    p1 = t + w1.norm(r2);
    p2 = t + w2.norm(r2);


    pt q1 = s + w1.norm(r1);
    pt q2 = s + w2.norm(r1);



    pt g1 = (p1 - q1);
    pt g2 = (p2 - q2);

    g1 = q1 + g1.norm(sqrtl(R * R - r1 * r1));
    g2 = q2 + g2.norm(sqrtl(R * R - r1 * r1));


    //cout << g1.x << " " << g1.y << " " << g2.x << " " << g2.y << "\n";

    db ans = getS(p1, p2, g2) + getS(g1, g2, p1) + getFunc(p1, p2, t, r2) + getFunc(g1, g2, s, R);
    cout.precision(10);
    cout << fixed << (100 * ans) / (pi * R * R);
}
