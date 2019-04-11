#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define TASK "polygon"

struct pt {
    double x, y;

    pt() {}
    pt(double x, double y): x(x), y(y) {}
    pt(pt A, pt B): x(B.x - A.x), y(B.y - A.y) {}

    void norm(double q) {
        double t = dist();
        x = x * q / t;
        y = y * q / t;
    }

    double operator * (pt b) { return x * b.x + y * b.y; }
    double operator % (pt b) { return x * b.y - y * b.x; }

    double dist() { return sqrt(x * x + y * y); }
};

struct line {
    double a, b, c;

    line() {}
    line(pt A, pt B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }

    double dist(pt Q) {
        return (a * Q.x + b * Q.y + c) / sqrt(a * a + b * b);
    }
};

vector<pt> cur;

bool in(pt A, pt B, pt M) {
    return min(A.x, B.x) <= M.x && M.x <= max(A.x, B.x) &&
            min(A.y, B.y) <= M.y && M.y <= max(A.y, B.y);
}

void make(pt A, pt B, pt O, double R) {

    line m(A, B);

    double d = m.dist(O);
    pt N(m.a, m.b);
    pt M(-m.b, m.a);

    N.norm(-d);

    pt H(O.x + N.x, O.y + N.y);

    double dist = sqrt(R * R - d * d);
    M.norm(dist);

    pt K(H.x - M.x, H.y - M.y);
    pt L(H.x + M.x, H.y + M.y);



    if (in(A, B, K)) {
        cur.push_back(K);
    }
    if (in(A, B, L)) {
        cur.push_back(L);
    }
}

const double pi = atan2(1, 1) * 4.0;

double getangle(pt A, pt B) {
    double a = atan2(A % B, A * B);
    if (a < 0) a += 2 * pi;
    return a * 180 / pi;
}

pt O(0, 0);

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN

    int n;
    cin >> n;


    vector<pt> P(n);
    for (int i = 0; i < n; i++) cin >> P[i].x >> P[i].y;


    double dx = -P[0].x;
    double dy = -P[0].y;

    for (int i = 0; i < n; i++) P[i].x += dx, P[i].y += dy;

    int m;
    cin >> m;

    cout.precision(10);
    cout << fixed;

    for (int it = 0; it < m; it++) {

        pt Q;
        cin >> Q.x >> Q.y;

        Q.x += dx, Q.y += dy;


        cur.clear();

        for (int i = 0; i < n; i++) {
            pt A = P[i], B = P[(i + 1) % n];
            make(A, B, O, Q.dist());
        }

        if (cur.empty()) {
            cout << "360 360\n";
            continue;
        }

        cur.push_back(Q);

        sort(cur.begin(), cur.end(), [](pt A, pt B) {
            if (A.y <= 0 && B.y > 0) return true;
            if (A.y > 0 && B.y <= 0) return false;
            ll t = A % B;
            if (t == 0) return A.x < B.x;
            return t > 0;
        });

        //for (auto c : cur) cout << c.x << " " << c.y << "\n";

        for (int i = 0; i < (int)cur.size(); i++) if (cur[i].x == Q.x && cur[i].y == Q.y) {

            pt A = cur[(i - 1 + (int)cur.size()) % (int)cur.size()];
            pt B = cur[(i + 1) % (int)cur.size()];

            cout << getangle(Q, B) << " " << getangle(A, Q) << "\n";
            break;
        }
    }

    return 0;
}


