#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (1 << 17) + 3;

ll dp[dd];
ll cnt[dd][21], sumcnt[dd];

int main() {
	int n, m;
	cin >> n >> m;
	
	vector<vector<int> > E(n);
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		E[a - 1].push_back(b - 1);
	}
	
	for (int v = 0; v < n; v++) {
		for (int to : E[v]) {
			cnt[(1 << v) | (1 << to)][to] = 1;
		}
	}
	
	for (int msk = 0; msk < (1 << n); msk++) {
		for (int last = 0; last < n; last++) if (cnt[msk][last] && ((msk >> last) & 1)) {
			for (int to : E[last]) if (((msk >> to) & 1) == 0){
				cnt[msk ^ (1 << to)][to] += cnt[msk][last];
			}
		}
	}
	
	for (int msk = 0; msk < (1 << n); msk++) {
		for (int last = 0; last < n; last++) {
			sumcnt[msk] += cnt[msk][last];
		}
	}
	
	dp[0] = 1;
	for (int msk = 1; msk < (1 << n); msk++) {
		int mx = -1;
		for (int i = 0; i < n; i++) if ((msk >> i) & 1) mx = i;
		assert(mx != -1);
		
		for (int pmsk = msk; pmsk > 0; pmsk = (pmsk - 1) & msk) {
			if ((pmsk >> mx) & 1) dp[msk] += dp[msk ^ pmsk] * sumcnt[pmsk];
		}
	}
	cout << dp[(1 << n) - 1] << "\n";
	return 0;
}