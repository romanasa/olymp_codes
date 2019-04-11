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

int get(int n) {
	return bp(2, n * (n - 1) / 2);
}

int dp[321];
int C[321][321];
#define TASK "graphs"
int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	for (int i = 0; i <= 300; i++) C[0][0] = 0;
	for (int i = 0; i <= 300; i++) C[i][0] = 1;
	
	for (int i = 1; i <= 300; i++) {
		for (int j = 1; j <= 300; j++) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}
	}

	int n=300;
	dp[1] = 0;
		for (int i = 2; i <= n; i++) {
			dp[i] = 0;
			for (int j = 1; j < i; j++) {
				int c = get(j) - dp[j];
				if (c < 0) c += mod;
				c = 1ll * c * get(i - j) % mod;
				c = 1ll * c * C[i][j] % mod;
				c = 1ll * c * j % mod;
				
				dp[i] += c;
				if (dp[i] >= mod) dp[i] -= mod;
			}
			dp[i] = 1ll * dp[i] * bp(i, mod - 2) % mod;
		}
	while (cin >> n) {
		
		int ans = get(n) - dp[n];
		cout << (ans < 0 ? ans + mod : ans) << "\n";
	}
	return 0;
}