#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = 998244353;

int C[234][234];

#define TASK "derangements"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	cin >> n;
	
	vector<int> fact(n + 1), p(n + 1);
	
	fact[0] = 1;
	for (int i = 1; i <= n; i++) fact[i] = 1ll * fact[i - 1] * i % mod;
	
	p[0] = 1;
	for (int i = 1; i <= n; i++) p[i] = 1ll * p[i - 1] * 2 % mod;
	
	for (int i = 0; i <= n; i++) C[0][0] = 0;
	for (int i = 0; i <= n; i++) C[i][0] = 1;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}
	}
	
	int ans = 0;
	for (int i = n; i >= 0; i--) {
		
		int cur = 1ll * C[n][i] * fact[i] % mod;
		cur = 1ll * cur * p[i] % mod;
	
	
		if ((n - i) % 2 == 0) {
			ans = (ans + cur) % mod;
		} else {
			ans = (ans - cur + mod) % mod;
		}
	
	}
	cout << ans << "\n";
	return 0;
}