#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct pt {
    ll x, y;

    pt() {}
    pt(ll x, ll y): x(x), y(y) {}
    pt(pt A, pt B): x(B.x - A.x), y(B.y - A.y) {}

    pt operator + (pt b) { return pt(x + b.x, y + b.y); }
};

int bad[7];
pt P[7];
int ind;

void out() {

    cout << "POSSIBLE\n";
    cout.precision(5);
    cout << fixed;

    cout << P[0].x << " " << P[0].y << "\n";
    cout << (P[0].x + P[2].x) / 2.0 << " " << (P[0].y + P[2].y) / 2.0 << "\n";
    cout << P[2].x << " " << P[2].y << "\n";
    cout << (P[4].x + P[2].x) / 2.0 << " " << (P[4].y + P[2].y) / 2.0 << "\n";
    cout << P[4].x << " " << P[4].y << "\n";
    cout << (P[0].x + P[4].x) / 2.0 << " " << (P[0].y + P[4].y) / 2.0 << "\n";
    exit(0);
}

int main() {
    freopen("castle.in", "r", stdin);
    freopen("castle.out", "w", stdout);

    for (int i = 0; i < 6; i++) {
        string a, b;
        cin >> a >> b;

        if (a == "?") bad[i] = 1;
        else {
            P[i].x = atoi(a.c_str());
            P[i].y = atoi(b.c_str());
            ind++;
        }
    }

    if (ind <= 2) return 0 * puts("IMPOSSIBLE");
    if (ind == 3) {
        if (!bad[0] && !bad[1] && !bad[2]) return 0 * puts("IMPOSSIBLE");
        if (!bad[2] && !bad[3] && !bad[4]) return 0 * puts("IMPOSSIBLE");
        if (!bad[4] && !bad[5] && !bad[0]) return 0 * puts("IMPOSSIBLE");
    }

    if (!bad[0] && !bad[2] && !bad[4]) out();

    if (!bad[1] && !bad[3] && !bad[5]) {
        P[0] = P[1] + pt(P[3], P[5]);
        P[2] = P[1] + pt(P[5], P[3]);
        P[4] = P[5] + pt(P[1], P[3]);
        out();
    }

    for (int it = 0; it < 2; it++) {

        if (!bad[0] && !bad[1]) P[2] = P[1] + pt(P[0], P[1]), bad[2] = 0;
        if (!bad[2] && !bad[1]) P[0] = P[1] + pt(P[2], P[1]), bad[0] = 0;

        if (!bad[2] && !bad[3]) P[4] = P[3] + pt(P[2], P[3]), bad[4] = 0;
        if (!bad[4] && !bad[3]) P[2] = P[3] + pt(P[4], P[3]), bad[2] = 0;

        if (!bad[4] && !bad[5]) P[0] = P[5] + pt(P[4], P[5]), bad[0] = 0;
        if (!bad[0] && !bad[5]) P[4] = P[5] + pt(P[0], P[5]), bad[4] = 0;
    }
    out();
    return 0;
}

