#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = (int)1e6 + 3;

ll bp(ll a, ll n) {
    if (n == 0) return 1;
    if (n & 1) return bp(a, n - 1) * a % mod;
    ll t = bp(a, n / 2);
    return t * t % mod;
}

const int dd = (int)1e6 + 1;

ll fact[dd], tcaf[dd];
ll S[dd];

ll C(ll n, ll k) {
    if (n < k) return 0;
    return fact[n] * tcaf[k] % mod * tcaf[n - k] % mod;
}

int main() {
#ifdef WIN
    freopen("input.txt", "r", stdin);
#endif
    int n, c;
    cin >> n >> c;
    fact[0] = tcaf[0] = 1;

    for (int i = 1; i < dd; i++) fact[i] = fact[i - 1] * i % mod;

    tcaf[dd - 1] = bp(fact[dd - 1], mod - 2);
    for (int i = dd - 2; i; i--) tcaf[i] = tcaf[i + 1] * (i + 1) % mod;

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += C(i + c - 1, i);
        ans %= mod;
    }
    cout << ans << "\n";
	return 0;
}

