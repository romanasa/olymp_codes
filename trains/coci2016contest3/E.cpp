#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

const int dd = (int)2e5 + 7;
const int mod = (int)1e9 + 7;
int a[dd], G[dd];

struct Fen {
    pair<int, int> T[dd];

    void add(int &a, int b) {
        a += b;
        if (a >= mod) a -= mod;
    }
    void upd(pair<int, int> &a, pair<int, int> b) {
        if (a.first < b.first) a = b;
        else if (a.first == b.first) add(a.second, b.second);
    }
    void upd(int pos, pair<int, int> val) {
        for (int i = pos + 5; i < dd; i += (i&-i)) {
            upd(T[i], val);
        }
    }
    pair<int, int> get(int pos) {
        pair<int, int> res(0, 0);
        for (int i = pos + 5; i ; i -= (i&-i)) upd(res, T[i]);
        return res;
    }
} F1, F2;

pair<int, int> Q[dd], Q2[dd];
int cnt[dd];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) G[i] = a[i];

    sort(G, G + n);
    int iG = unique(G, G + n) - G;

    for (int i = 0; i < n; i++) a[i] = lower_bound(G, G + iG, a[i]) - G, cnt[a[i]]++;

    F2.upd(-1, make_pair(0, 1));
    for (int i = n - 1; i >= 0; i--) {
        auto c = F2.get(n - (a[i] + 1));
        c.first++;
        F2.upd(n - a[i], c);
        F2.upd(Q2[a[i]], c);

        //err("upd %d, (%d, %d)\n", a[i], c.first, c.second);
    }

    F1.upd(-1, make_pair(0, 1));
    for (int i = n - 1; i >= 0; i--) {
        auto c = F1.get(a[i] - 1);
        c.first++;
        F1.upd(a[i], c);
        F1.upd(Q[a[i]], c);
    }


    Q2[iG] = make_pair(0, 1);
    for (int x = iG - 1; x > 0; x--) {
        F2.upd(Q2[x], Q2[x + 1]);
    }
    int len = 0;

    for (int x = 0; x < iG; x++) {
        auto c1 = Q[x];
        auto c2 = Q2[x + 1];
        len = max(len, c1.first + c2.first);
    }

    int ans = 0;
    for (int x = 0; x < iG; x++) {
        auto c1 = Q[x];
        auto c2 = Q2[x + 1];
        //if (c2 == make_pair(0, 1)) continue;

        if (len == c1.first + c2.first) {
            //err("x = %d, c1 = (%d, %d), c2 = (%d, %d)\n", x, c1.first, c1.second, c2.first, c2.second);
            int cur = 1ll * c1.second * c2.second % mod;
            F1.add(ans, cur);
        }
    }
    int p = 1;
    for (int i = len; i < n; i++) F1.add(p, p);
    ans = 1ll * ans * p % mod;

    if (*max_element(a, a + n) != *min_element(a, a + n) && ans > 1) {
        if (ans % 2) ans += mod;
        ans /= 2;
    }

    cout << len << " " << ans << "\n";
    return 0;
}
