#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#define x first
#define y second
#define mp make_pair
#define pub push_back
#define all(v) (v).begin(), (v).end()
//236695ZVSVG

using namespace std;

typedef long long ll;
typedef double db;

const int dd = (int)1e5 + 7;
ll Q[dd];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    int n;
    cin >> n;


    for (int i = 0; i < n; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        Q[l] += x, Q[r] -= x;
    }

    ll cur = 0, ans = 0;
    for (int i = 0; i < dd; i++) {
        cur += Q[i];
        ans = max(ans, cur);
    }
    cout << ans;
    return 0;
}

