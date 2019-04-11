#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2007;

int A[dd];
map<pair<int, int>, ll> dp[dd];
int I[dd][dd];

ll go(int l, int r, int k, int d) {
	if (!k) return 0;
	if (l > r) return (ll)1e18;
	if (r - l + 1 < k) return (ll)1e18;

	if (dp[k].count({ l, r })) return dp[k][{ l, r }];
	
	int ind = I[l][r];
	int t = (ind - 1) - l + 1;

	//err("l = %d, r = %d, k = %d, t = %d\n", l, r, k, t);
	
	ll cur = (ll)1e18;	
	for (int i = 0; i <= min(t, k - 1); i++) {
		cur = min(cur, go(l, ind - 1, i, A[ind]) + go(ind + 1, r, k - i - 1, A[ind]) + A[ind] - d);
	}
	//err("l = %d, r = %d, k = %d, cur = %I64d\n", l, r, k, cur);
	return dp[k][{ l, r }] = cur;
}

#define TASK "dibbles"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, k;
	scanf("%d %d", &n, &k);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}
	
	for (int i = 0; i < n; i++) {
		int ind = i;
		for (int j = i; j < n; j++) {
			if (A[j] < A[ind]) ind = j;
			I[i][j] = ind;
		}
	}
	
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (go(0, n - 1, i, 0) <= k)
			ans = i;
	}
	printf("%d\n", ans);
	return 0;
}