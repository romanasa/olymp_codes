#include <bits/stdc++.h>
#define ll long long

using namespace std;

int dp[600][600];

void upd(int &a, int b) { if (a > b) a = b; }

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	int q;
	scanf("%d", &q);

	for (int i = 0; i <= 600; i++) {
		for (int j = 0; j <= 600; j++) {
			dp[i][j] = i * j;
		}
	}
	
	while (q--) {
		int x, y;
		scanf("%d %d", &x, &y);
		dp[x][y] = 0;
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int t = 1; t < i; t++) {
				upd(dp[i][j], dp[t][j] + dp[i - t][j]);
			}
			for (int t = 1; t < j; t++) {
				upd(dp[i][j], dp[i][t] + dp[i][j - t]);
			}
		}
	}
	printf("%d\n", dp[n][m]);
	return 0;
}