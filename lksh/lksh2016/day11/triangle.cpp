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

#define TASK "triangle"

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
    double x, y;
    pt() {}
    pt(double x, double y) : x(x), y(y) {}
    double operator % (pt b) {
        return x * b.y - y * b.x;
    }
};

struct line {
    double a, b, c;
    line() {}
    line(pt A, pt B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }
    int get(pt A) {
        return (a * A.x + b * A.y + c) >= 0;
    }
    void neg() {
        a *= -1;
        b *= -1;
        c *= -1;
    }
};

pt inter(line m, line n) {
    double x = -(m.c * n.b - n.c * m.b) / (m.a * n.b - n.a * m.b);
    double y = -(m.a * n.c - n.a * m.c) / (m.a * n.b - n.a * m.b);
    return pt(x, y);
}

double sq(vector<pt> P) {
    double S = 0;
    forn(i, P.size()) {
        S += P[i] % P[(i + 1) % P.size()];
    }
    return abs(S / 2);
}

double get(vector<line> T) {
    vector<pt> P = { pt(-10001, -10001), pt(10001, -10001), pt(10001, 10001), pt(-10001, 10001) };

    for (auto a : T) {
        vector<pt> G;

        forn(i, P.size()) {
            pt A = P[i], B = P[(i + 1) % P.size()];

            if (a.get(A)) G.push_back(A);
            
            if (a.get(A) != a.get(B)) {
                pt X = inter(a, line(A, B));
                G.push_back(X);
            }   
        }

        P = G;
    }
    return sq(P);
}

int solve() {
    vector<pt> A(3), B(3);

    forn(i, 3)
        cin >> A[i].x >> A[i].y;
    forn(i, 3)
        cin >> B[i].x >> B[i].y;


    double ans = sq(A) + sq(B);

    vector<line> P;
    forn(i, 3) {
        P.push_back(line(A[i], A[(i + 1) % 3]));

        auto B = A[(i + 2) % 3];

        if (!P.back().get(B))
            P.back().neg();
    }
    
    forn(i, 3) {
        P.push_back(line(B[i], B[(i + 1) % 3]));

        auto A = B[(i + 2) % 3];

        if (!P.back().get(A))
            P.back().neg();
    }

    ans -= get(P);

    printf("%.10f", ans);
    return 0;
}