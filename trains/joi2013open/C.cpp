#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 2007;

int dp[dd][dd];
int a[dd];
int n, p, q;

bool check(int w) {
	for (int i = 0; i <= n; i++)
		fill(dp[i], dp[i] + dd, (int)2e9);
	
	dp[0][0] = 0;
	
	for (int i = 1; i <= n; i++) {	
	
		int j1 = lower_bound(a, a + n, a[i - 1] - w + 1) - a;
		int j2 = lower_bound(a, a + n, a[i - 1] - w - w + 1) - a;
	
		for (int x = 0; x <= min(p, i); x++) {
			if (x) dp[i][x] = min(dp[i][x], dp[j1][x - 1]);
			dp[i][x] = min(dp[i][x], dp[j2][x] + 1);
		}	
	}
	for (int x = 0; x <= p; x++) if (dp[n][x] <= q) return 1;
	return 0;
}

int main() {
	cin >> n >> p >> q;
	
	for (int i = 0; i < n; i++) cin >> a[i];
	sort(a, a + n);
	
	p = min(p, n);
	q = min(q, n);
	
	int l = -1, r = (int)1e9 + 1;
	
	while (r - l > 1) {
		int m = (l + r) / 2;
		if (check(m)) r = m;
		else l = m;
	}
	cout << r << "\n";
	return 0;
}