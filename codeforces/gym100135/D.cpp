#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int cost[11][11];
int dp[11][11];

#define TASK "king2"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n = 8;
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> cost[i][j];
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) dp[i][j] = (int)1e9;
	
	dp[n - 1][0] = 0;
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			if (i + 1 < n) dp[i][j] = min(dp[i][j], dp[i + 1][j]);
			if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j - 1]);
			if (i + 1 < n && j > 0) dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
			dp[i][j] += cost[i][j];
		}
	}
	cout << dp[0][n - 1] << "\n";
	
	return 0;
}