#include <bits/stdc++.h>
#ifdef SIR
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#else
#define err(...) 42
#endif

typedef long long ll;

using namespace std;

ll solve(vector<int> &a, vector<int> &b) {
    int n = (int)a.size();
    vector<pair<int, int>> c(n);
    for (int i = 0; i < n; i++) c[i] = { a[i] + b[i], i };
    sort(c.rbegin(), c.rend());

    ll sum = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) sum += a[c[i].second];
        else sum -= b[c[i].second];
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef SIR
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    cout << solve(a, b);
    return 0;
}