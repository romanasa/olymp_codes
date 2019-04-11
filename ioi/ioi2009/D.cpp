#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int inf = (int)1e9 + 1;
int dp[51][51][51][51];
int P[57][57];

inline int get(int i1, int j1, int i2, int j2) {
	return P[i2][j2] - P[i1 - 1][j2] - P[i2][j1 - 1] + P[i1 - 1][j1 - 1];
}

int F(int i1, int j1, int i2, int j2) {
	if (i1 > i2 || j1 > j2)
		return 0;
	if (i1 == i2 && j1 == j2)
		return 0;
	if (dp[i1][j1][i2][j2])
		return dp[i1][j1][i2][j2];

	dp[i1][j1][i2][j2] = inf;
	
	for (int i = i1; i < i2; i++) {
		dp[i1][j1][i2][j2] = min(dp[i1][j1][i2][j2], F(i1, j1, i, j2) + F(i + 1, j1, i2, j2) + get(i1, j1, i2, j2));
	}
	
	for (int j = j1; j < j2; j++)  {
		dp[i1][j1][i2][j2] = min(dp[i1][j1][i2][j2], F(i1, j1, i2, j) + F(i1, j + 1, i2, j2) + get(i1, j1, i2, j2));
	}
	
	return dp[i1][j1][i2][j2];
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int t;
			scanf("%d", &t);
			P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + t;
		}
	}
	printf("%d\n", F(1, 1, n, m));
	return 0;
}