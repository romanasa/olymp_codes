#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

ll calc(ll x, ll i) {
	if (x == -1) return 0;
	ll t = x / (1ll << (i + 1));
	ll q = max(0ll, x - t * (1ll << (i + 1)) - (1ll << i));
	if ((x >> i) & 1) q++;
	return t * (1ll << i) + q;
}

//000
//001
//010
//011
//100
//101
//110
//111

const ll mod = (ll)1e9 + 1;

int main() {

	int k, t;
	scanf("%d %d", &k, &t);
	
	while (t--) {
		int a, b;
		scanf("%d %d", &a, &b);

		ll res = 0;	
		for (int i = 0; i < k; i++) {
			res += 1ll * (1ll << (k - i - 1)) * (calc(b, i) - calc(a - 1, i)) % mod;
			res %= mod;
		}
		printf("%lld\n", res);
	}
	
	return 0;
}