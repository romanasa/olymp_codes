#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

int solve(int n) {
	vector<int> dp(n + 1, 0);
	dp[n] = 0;
	for (int i = n - 1; i > 0; i--) {
		dp[i] = 0;
		if (!dp[i + 1] || 2 * i <= n && !dp[2 * i])
			dp[i] = 1;
	}
	return dp[1];
}

ll calc(ll x) {
	ll cnt = 0;
	for (int i = 1; i < 60; i += 2) {
		if (x < (1ll << i)) break;
		ll cur = 0;
		for (int q = 1; q <= i; q += 2) cur ^= (1ll << q);
		if (x >= cur) cnt += (1ll << (i / 2));
		else {
			x -= (1ll << i);
			cnt += calc(x) + 1;
			break;
		}
	}
	return cnt;
}

#define TASK "game"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ll l, r;
	cin >> l >> r;
	cout << calc(r) - calc(l - 1) << "\n";
	return 0;
}