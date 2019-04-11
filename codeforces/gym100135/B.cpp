#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int dp[1234];

#define TASK "lepus"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	cin >> n;
	
	string s;
	cin >> s;
	
	fill(dp, dp + n + 1, -1);
	dp[0] = 0;
	
	for (int i = 0; i < n; i++) if (dp[i] != -1) {
		if (s[i] != 'w') dp[i + 1] = max(dp[i + 1], dp[i] + (s[i] != '.'));
		if (i == 0) continue;
		if (i + 2 < n && s[i + 2] != 'w') dp[i + 3] = max(dp[i + 3], dp[i] + (s[i + 2] != '.'));
		if (i + 4 < n && s[i + 4] != 'w') dp[i + 5] = max(dp[i + 5], dp[i] + (s[i + 4] != '.'));
	}
	cout << dp[n] << "\n";
	return 0;
}