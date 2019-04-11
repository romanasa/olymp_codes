#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int dp[21][21][167];


int main() {
	int n, k, s;
	while (cin >> n >> k >> s) {
		if (n == 0 && k == 0 && s == 0) break;
	
		for (int i = 0; i <= k; i++) {
			for (int j = 0; j <= n; j++) {
				for (int k = 0; k <= s; k++) dp[i][j][k] = 0;
			}
		}
		dp[0][0][0] = 1;
		
		for (int i = 0; i < k; i++) {
			for (int j = 0; j <= n; j++) {
				for (int t = 0; t <= s; t++) if (dp[i][j][t]) {
				
					for (int q = j + 1; q <= n && q + t <= s; q++) {
						dp[i + 1][q][t + q] += dp[i][j][t];
					}
				}
			}
		}
		int ans = 0;
		for (int x = 0; x <= n; x++) ans += dp[k][x][s];
		cout << ans << "\n";
	}
	return 0;
}