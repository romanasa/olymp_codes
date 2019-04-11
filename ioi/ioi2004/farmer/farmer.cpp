#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int dd = 150 * 1000 + 1;
int dp[dd];

int main() {
	int q, n, m;
	scanf("%d %d %d", &q, &n, &m);
	
	vector<int> A(n), B(m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}
	
	for (int i = 0; i < m; i++) {
		scanf("%d", &B[i]);
	}
	
	fill(dp, dp + dd, -(int)1e9);
	dp[0] = 0;
	
	for (int i = 0; i < n; i++) {
		for (int j = q; j >= A[i]; j--) {
			if (dp[j - A[i]] != -(int)1e9)
				dp[j] = max(dp[j], dp[j - A[i]] + A[i]);
		}
	}
	
	int ans = 0;
	int cur = q;
	while (dp[cur] == -(int)1e9) cur--;
	
	if (cur >= q - 1) {
		return 0 * printf("%d\n", cur);
	}
	
	sort(B.rbegin(), B.rend());
	
	int h = 0, d = q - cur;
	for (int i = 0; i < m; i++) {
		if (h + B[i] > d) {
			ans += d - h - 1;
			break;
		} else {
			h += B[i];
			ans += B[i] - 1;
		}
	}
	
	int t = ans + cur;
	
	for (int i = 0; i < n; i++) {
		if (A[i] >= q) {
			t = max(t, q - 1);
		}
	}
	
	printf("%d\n", t);
	
	
	return 0;
}