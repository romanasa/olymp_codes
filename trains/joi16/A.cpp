#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e4 + 7;
int A[dd];
ll dp[dd];

int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 0; i < n; i++) scanf("%d", &A[i]);
	
	fill(dp, dp + n + 1, (ll)1e18);
	dp[0] = 0;
	
	for (int i = 1; i <= n; i++) {
		int mn = (int)1e9 + 1, mx = -1;
		for (int j = i; j > max(i - m, 0); j--) {
			mn = min(mn, A[j - 1]);
			mx = max(mx, A[j - 1]);
			dp[i] = min(dp[i], dp[j - 1] + k + 1ll * (i - j + 1) * (mx - mn));
		}
	}
	printf("%I64d\n", dp[n]);
	return 0;
}