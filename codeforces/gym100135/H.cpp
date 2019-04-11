#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

ll dp[2007][2007];

#define TASK ""

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) dp[i][i] = 1;
	
	for (int s = 1; s <= n; s++) {
		for (int j = 1; j <= s; j++) if (dp[s][j]) {
			for (int k = 2 * j; s + k <= n; k++) {
				dp[s + k][k] += dp[s][j];
			}
		}
	}
	
	ll ans = 0;
	for (int i = 1; i <= n; i++) ans += dp[n][i];
	cout << ans << "\n";
	
	return 0;
}