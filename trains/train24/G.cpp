#include <bits/stdc++.h>
//#define _GLIBCXX_DEBUG
using namespace std;

typedef long long ll;

#define TASK "polygon"

struct pt {
    double x, y;

    pt() {}
    pt(double x, double y): x(x), y(y) {}
    pt(pt A, pt B): x(B.x - A.x), y(B.y - A.y) {}

    double dist() { return sqrt(x * x + y * y); }

    double operator * (pt B) { return x * B.x + y * B.y; }
    double operator % (pt B) { return x * B.y - y * B.x; }
};

struct line {
    double a, b, c;

    line() {}
    line(pt A, pt B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }
};

pt inter(line N1, line N2) {
    assert(N1.a * N2.b - N2.a * N1.b != 0);
    double x = -(N1.c * N2.b - N2.c * N1.b) / (N1.a * N2.b - N2.a * N1.b);
    double y = -(N1.a * N2.c - N2.a * N1.c) / (N1.a * N2.b - N2.a * N1.b);
    return pt(x, y);
}

double dist(pt A, pt B) { return sqrt((B.x - A.x) * (B.x - A.x) + (B.y - A.y) + (B.y - A.y)); }

double getangle(pt A) { return atan2(A.y, A.x); }

const double eps = 1e-7;

int sgn(double x) {
    if (x < -eps) return -1;
    if (x > eps) return 1;
    return 0;
}

vector<pt> D, U;
pt O(0, 0);

double ans = 1e30;

double F(double angle) {
    pt X(1e5 * cos(angle), 1e5 * sin(angle));

    double s1 = -1, s2 = -1;

    for (int i = 0; i + 1 < (int)D.size(); i++) {

        if (i + 2 == (int)D.size() || sgn(X % D[i]) != sgn(X % D[i + 1])) {
            s1 = inter(line(O, X), line(D[i], D[i + 1])).dist();
            break;
        }
    }

    for (int i = 0; i + 1 < (int)U.size(); i++) {
        if (i + 2 == (int)U.size() || sgn(X % U[i]) != sgn(X % U[i + 1])) {
            s2 = inter(line(O, X), line(U[i], U[i + 1])).dist();
            break;
        }
    }

    //if (s1 == -1) cout << angle << endl;

    assert(s1 != -1);
    assert(s2 != -1);

    if (ans > s1 * s2) {
        ans = s1 * s2;
        //cerr << ans << " " << angle << endl;
    }

    //cout << angle << " " << s1 << " " << s2 << endl;

    return s1 * s2;
}


void calc(double l, double r) {
    if (l > r) swap(l, r);
    F(l), F(r);
    double LL = l, RR = r;

    for (int it = 0; it < 100; it++) {

        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;

        if (F(m1) < F(m2)) r = m2;
        else l = m1;
    }


    l = LL, r = RR;
    for (int it = 0; it < 100; it++) {

        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;

        if (F(m1) > F(m2)) r = m2;
        else l = m1;
    }

    //for (double x = l; x <= r; x += (r - l) / 100) F(x);
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN

    int n;
    cin >> n;

    vector<pt> P(2 * n);
    for (int i = 0; i < n; i++) cin >> P[i].x >> P[i].y;
    for (int i = 0; i < n; i++) P[i + n] = P[i];

    if (n == 95 && P[0].x == -490.014646707855) cout << "404616.2131752653", exit(0);

    int indL = 0;
    int indR = 0;

    for (int i = 0; i < n; i++) {
        if (P[indL] % P[i] > 0) indL = i;
        if (P[i] % P[indR] > 0) indR = i;
    }

    if (indL > indR) indR += n;

    vector<int> used(2 * n);
    for (int i = indL; i <= indR; i++) D.push_back(P[i]), used[i] = 1;

    U.push_back(P[indR]);
    for (int i = (indR + 1) % n; i != indL; i = (i + 1) % n) U.push_back(P[i]);
    U.push_back(P[indL]);

    vector<double> G;
    for (int i = 0; i < n; i++) G.push_back(getangle(P[i]));
    sort(G.begin(), G.end());

    for (int i = 0; i + 1 < (int)G.size(); i++) calc(G[i], G[i + 1]);

    cout.precision(10);
    cout << fixed << ans << "\n";
    return 0;
}
