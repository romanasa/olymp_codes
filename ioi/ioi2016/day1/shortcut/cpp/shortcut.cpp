#include "shortcut.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

typedef long long ll;

const ll linf = (ll)1e18 + 1;
const int dd = (int)3e5 + 7;

ll x[dd];
int cur[dd];

inline void updMax(ll &a, ll b) { if (a < b) a = b; }

struct Fen {
    ll T[dd];

    inline void clear() { fill(T, T + dd, -linf); }

    inline void upd(int v, ll val) {
        for (int i = dd - v - 1; i < dd; i += (i&-i))
            updMax(T[i], val);
    }

    inline ll get(int v) {
        ll res = -linf;
        for (int i = dd - v - 1; i; i -= (i&-i))
            updMax(res, T[i]);
        return res;
    }
} B;

ll find_shortcut(int n, vector<int> l, vector<int> d, int c) {
    for (int i = 1; i < n; i++)
        x[i] = x[i - 1] + l[i - 1];


    vector<ll> G;
    for (int i = 0; i < n; i++) {
        G.push_back(x[i] + d[i]);
    }

    sort(G.begin(), G.end());
    G.resize(unique(G.begin(), G.end()) - G.begin());

    for (int i =0; i < n; i++) {
        cur[i] = lower_bound(G.begin(), G.end(), x[i] + d[i]) - G.begin();
    }

    ll L = 0, R = x[n - 1] + 2 * (*max_element(d.begin(), d.end())) + 7;

    while (R - L > 1) {
        ll m = (L + R) / 2;

        ll minS = -linf;
        ll maxS = linf;
        ll minD = -linf;
        ll maxD = linf;

        B.clear();

        ll maxV = -linf;

        for (int i = n - 1; i >= 0; i--) {

            if (i == n - 1) {
                updMax(maxV, d[i] + x[i]);
                B.upd(cur[i], d[i] - x[i]);
                continue;
            }

            int ind = upper_bound(G.begin(), G.end(), m + x[i] - d[i]) - G.begin();

            ll b = B.get(ind);

            if (maxV > m + x[i] - d[i]) {
                minS = max(minS, -m + c + x[i] + d[i] + maxV);
                maxD = min(maxD, -c + m + x[i] - d[i] - maxV);
            }

            if (b != -linf) {
                minD = max(minD, -m + c + x[i] + d[i] + b);
                maxS = min(maxS, -c + m + x[i] - d[i] - b);
            }

            updMax(maxV, d[i] + x[i]);
            B.upd(cur[i], d[i] - x[i]);
        }

        int ok = 0;

        int l1 = n, r1 = n;
        int l2 = 0, r2 = 0;

        for (int i = 0; i < n; i++) {

            while (l1 > 0 && x[l1 - 1] >= minS - x[i]) l1--;
            while (r1 > 0 && x[r1 - 1] > maxS - x[i]) r1--;

            while (l2 < n && x[l2] < x[i] - maxD) l2++;
            while (r2 < n && x[r2] <= x[i] - minD) r2++;

            if (max(l1, l2) < min(r1, r2) && i < min(r1, r2) - 1) {
                ok = 1;
                break;
            }
        }

        if (ok)
            R = m;
        else
            L = m;
    }
    return R;
}