#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct pt {
    ll x, y;
};

struct line {
    ll a, b, c;
    int ind;
    ll get(pt M) {
        return abs(a * M.x + b * M.y + c);
    }
};

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pt> P(n);
    for (int i = 0; i < n; i++) cin >> P[i].x >> P[i].y;

    int m;
    cin >> m;

    vector<line> T(m);
    for (int i = 0; i < m; i++) {
        cin >> T[i].a >> T[i].b >> T[i].c;
        T[i].ind = i;
    }

    sort(T.begin(), T.end(), [](line A, line B) {
        if (A.b <= 0 && B.b > 0) return true;
        if (A.b > 0 && B.b <= 0) return false;
        return A.a * B.b - A.b * B.a > 0;
    });

    auto prv = [&n](int i) {
        return i ? i - 1 : n - 1;
    };

    auto nxt = [&n](int i) {
        return i + 1 < n ? i + 1 : 0;
    };

    vector<double> ans(m);

    int j = 0;
    for (int i = 0; i < m; i++) {

        while (T[i].get(P[prv(j)]) < T[i].get(P[j])) j = prv(j);
        while (T[i].get(P[nxt(j)]) < T[i].get(P[j])) j = nxt(j);

        ans[T[i].ind] = T[i].get(P[j]) * 1.0 / sqrt(T[i].a * T[i].a + T[i].b * T[i].b);
    }
    for (int i = 0; i < m; i++) printf("%.5f\n", ans[i]);
    return 0;
}
