#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int get(int x, int c) {
	int cnt = 0;
	while (x) {
		cnt += (x % c == 1);
		x /= c;
	}
	return cnt;
}

int t2[31], t3[31], a[31];
ll dp[(1 << 20) + 7][20];

#define TASK "b"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) cin >> a[i];
	
	for (int i = 0; i < n; i++) {
		t2[i] = get(a[i], 2);
		t3[i] = get(a[i], 3);
	}
	
	for (int i = 0; i < n; i++) dp[1 << i][i] = 1;
	
	for (int msk = 0; msk < (1 << n); msk++) {
		for (int i = 0; i < n; i++) if (((msk >> i) & 1) && dp[msk][i]) {
			for (int j = 0; j < n; j++) if (((msk >> j) & 1) == 0 && (t2[i] == t2[j] || t3[i] == t3[j])) {
				dp[msk ^ (1 << j)][j] += dp[msk][i];
			}
		}
	}
	
	ll ans = 0;
	for (int i = 0; i < n; i++) ans += dp[(1 << n) - 1][i];
	cout << ans << "\n";
	
	return 0;
}