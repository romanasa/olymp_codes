#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int dp[12345];
vector<vector<int> > E;

int calc(int v) {
	if (dp[v] != -1) return dp[v];
	int cur = 0;
	for (int to : E[v]) cur = max(cur, calc(to) + 1);
	return dp[v] = cur;
}

#define TASK ""

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, m;
	cin >> n >> m;
	fill(dp, dp + n, -1);
	E.resize(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		E[a - 1].push_back(b - 1);
	}
	int ans = 0;
	for (int i = 0; i < n; i++) ans = max(ans, calc(i));
	cout << ans << "\n";
	return 0;
}