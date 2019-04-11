#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int dd = (int)1e6 + 7;

struct FenTree {
    ll T[dd];
    void upd(int pos, ll val) {
        for (int i = pos + 1; i < dd; i += (i&-i)) T[i] += val;
    }
    ll get(int pos) {
        ll res = 0;
        for (int i = pos + 1; i ; i -= (i&-i)) res += T[i];
        return res;
    }
} T1, T2, T3, T4;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int> > A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i].first >> A[i].second;
    }
    ll ans = 0;
    for (int it = 0; it < 2; it++) {
        sort(A.begin(), A.end());
        ll c1 = 0, c2 = 0;
        ll sum1 = 0, sum2 = 0;

        for (int i = 0; i < n; i++) {
            c2++, sum2 += A[i].first;
        }
        for (int i = 0; i < n; i++) {
            c2--, sum2 -= A[i].first;
            ans += (A[i].first * c1 - sum1) + (sum2 - A[i].first * c2);
            c1++, sum1 += A[i].first;
        }
        for (int i = 0; i < n; i++) swap(A[i].first, A[i].second);
    }
    cout << ans / (1ll * n * (n - 1)) << "\n";
    return 0;
}

