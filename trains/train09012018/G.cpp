#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = 998244353;

int bp(int a, int n) {
	if (!n) return 1;
	if (n & 1) return 1ll * bp(a, n - 1) * a % mod;
	int t = bp(a, n / 2);
	return 1ll * t * t % mod;
}

#define TASK "necklaces"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, k;
	cin >> n >> k;
	
	int ans = 0;
	
	for (int i = 1; i <= n; i++) {
		ans += bp(k, __gcd(i, n));
		ans %= mod;
	}
	
	ans = 1ll * ans * bp(n, mod - 2) % mod;
	cout << ans << "\n";
	
	
	return 0;
}