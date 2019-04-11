#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;
typedef double ld;

const int dd = (int)1e5 + 1;

int st[dd], sz;
int x[dd], y[dd];
ll dp[dd];

ll dist(int i, int j) {
	return 1ll * (x[i] - x[j]) * (x[i] - x[j]) + 1ll * (y[i] - y[j]) * (y[i] - y[j]);
}

#define TASK "icebergs"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &x[i], &y[i]);
	}
	
	
	dp[0] = 0;
	st[sz++] = 0;
	
	for (int i = 1; i < n; i++) {
		dp[i] = (ll)8e18;
		
		while (sz) {
			dp[i] = min(dp[i], max(dp[st[sz - 1]], dist(st[sz - 1], i)));
			if (y[st[sz - 1]] > y[i]) break;
			sz--;
		}
		st[sz++] = i;
	}
	
	printf("%.10f\n", sqrt(dp[n - 1]));	
	
	return 0;
}