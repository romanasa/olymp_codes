#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int a[31];
int dp[3][123456];

#define TASK "chimichangas"


int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> a[i];
	
	int maxC = k * *max_element(a, a + n);
	
	dp[0][0] = 1;
	for (int it = 0; it < k; it++) {
		int lvl = it & 1;
		int nxt = lvl ^ 1;
		fill(dp[nxt], dp[nxt] + maxC + 1, 0);	
		for (int x = 0; x <= maxC; x++) if (dp[lvl][x]) 
			for (int i = 0; i < n; i++) if (x + a[i] <= maxC)
				dp[nxt][x + a[i]] += dp[lvl][x];
	}
	int q;
	cin >> q;
	while (q--) {
		int x;
		cin >> x;
		if (x > maxC) puts("0");
		else printf("%d\n", dp[k & 1][x]);
	}
	return 0;
}