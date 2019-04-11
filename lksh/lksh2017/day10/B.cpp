#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const ll maxC = (ll)1e18 + 7;
ll A[31];
pair<int, ll> T[(1 << 15) + 1];

int n, m;

bool check(ll &a, ll b) {
	ll c = a;
	a *= b;
	return a / b == c;
}

ll calc(ll x) {
	ll res = 0;
	for (int msk = 0; msk < (1 << n); msk++) {
		res += T[msk].first * (x / T[msk].second);
	}
	return x - res;
}

int main() {
	scanf("%d %d", &n, &m);
	
	for (int i = 0; i < n; i++) scanf("%lld", &A[i]);
	
	for (int msk = 0; msk < (1 << n); msk++) {
		int c = 1;
		ll p = 1;
		for (int i = 0; i < n; i++) if ((msk >> i) & 1) {
			c = -c;
			ll t = __gcd(p, A[i]);
			p /= t;
			if (!check(p, A[i])) { p = maxC; break; }	
		}
		T[msk] = { c, p };
	}
	
	while (m--) {
		ll x;
		scanf("%lld", &x);
		ll l = 0, r = (ll)1e18 + 1;
		while (r - l > 1) {
			ll m = (l + r) / 2;
			if (calc(m) >= x) r = m;
			else l = m;
		}
		printf("%lld\n", r);
	}
	return 0;
}