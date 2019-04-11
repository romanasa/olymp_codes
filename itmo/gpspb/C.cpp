#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

#define TASK "chickens"

int dp[12345][13];

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n; cin >> n;
	
	vector<int> a(n), b(n);
	
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	
	dp[0][0] = 1;
	for (int msk = 0; msk < (1 << n); msk++) {
		for (int i = 0; i < n; i++) if (dp[msk][i]) {
			for (int j = 0; j < n; j++) if (((msk >> j) & 1) == 0) {
				if (a[j] <= b[i]) dp[msk ^ (1 << j)][i + 1] += dp[msk][i];
			}
		}
	}
	cout << dp[(1 << n) - 1][n] << "\n";
	return 0;
}