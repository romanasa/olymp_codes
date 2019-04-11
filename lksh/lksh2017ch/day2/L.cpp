#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

struct pt {
    ld x, y;
    pt() {}
    pt(int x, int y) : x(x), y(y) {}
    ld operator % (pt b) { return x * b.y - y * b.x; }
};

struct vt {
    ld x, y;
    vt() {}
    vt(pt A, pt B) { x = B.x - A.x, y = B.y - A.y; }
    ld operator % (vt b) { return x * b.y - y * b.x; }
};

bool inter(pt A, pt B, pt C, pt D) {
    return (vt(A, C) % vt(A, B)) * (vt(A, D) % vt(A, B)) <= 0 &&
            (vt(C, A) % vt(C, D)) * (vt(C, B) % vt(C, D)) <= 0;
}

bool check(vector<pt> &P) {
    int n = (int)P.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int k = (i + 1) % n;
            int t = (j + 1) % n;

            if (i == j || i == t || k == j || k == t) continue;
            if (inter(P[i], P[k], P[j], P[t])) return false;
        }
    }
    return true;
}

double sq(vector<pt> &P) {
    int n = (int)P.size();
    ld s = 0;
    for (int i = 0; i < n; i++)
        s += (P[i] % P[(i + 1) % n]);
    return abs(s / 2);
}

const int n = 7;
pt A[n + 1];
int P[n + 1];

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#endif
    int t;
    cin >> t;
    while (t--) {
        for (int i = 0; i < n; i++) cin >> A[i].x >> A[i].y;
        ld p;
        cin >> p;
        //cout << "ans: ";
        for (int i = 0; i < n; i++) P[i] = i;
        do {
            vector<pt> cur;
            for (int i = 0; i < n; i++) cur.push_back(A[P[i]]);
            if (check(cur)) {
                ld s = sq(cur);
                if (abs(s * s * s / 64 - p) < 1e-5) {
                    for (int i = 0; i < n; i++) cout << P[i] + 1 << " ";
                    break;
                }
            }
        } while (next_permutation(P, P + n));
        cout << "\n";
    }
    return 0;
}


