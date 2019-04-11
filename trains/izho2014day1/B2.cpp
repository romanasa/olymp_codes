#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int a[31], b[31];
int dp[(1 << 20) + 7];
int T[(1 << 20) + 7];
int cnt[(1 << 20) + 7];
int P[31];

void YES() { exit(0 * puts("YES")); }

void NO() { exit(0 * puts("NO")); }

inline void uax(int &a, int b) {
	if (a < b) a = b;
}

#define TASK "bank"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif

	for (int i = 1; i < (1 << 20); i++) cnt[i] = cnt[i >> 1] + (i & 1);

	int n, m;
	cin >> n >> m;
	
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> b[i];
	
	if (n == 1) {
		for (int msk = 0; msk < (1 << m); msk++) {
			int s = 0;
			for (int i = 0; i < m; i++) if ((msk >> i) & 1)
				s += b[i];
			if (s == a[0]) YES();
		}
		NO();
	}
	
	for (int msk = 0; msk < (1 << m); msk++) {
		int s = 0;
		for (int i = 0; i < m; i++) if ((msk >> i) & 1) s += b[i];
		T[msk] = s;
	}
	
	for (int i = 0; i < n; i++) P[i] = (i ? P[i - 1] : 0) + a[i];
	
	for (int msk = 0; msk < (1 << m); msk++) {
		if (dp[msk] == n) YES();
		int t = ((1 << m) - 1) ^ msk;
		int cur = dp[msk];
		for (int i = 0; i < m; i++) if (((msk >> i) & 1) == 0) {
			int nmsk = msk ^ (1 << i);
			if (T[nmsk] == P[cur]) uax(dp[nmsk], cur + 1);
			else uax(dp[nmsk], cur);
		}
	}
	NO();
	return 0;
}