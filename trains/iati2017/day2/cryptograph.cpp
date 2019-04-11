#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 400 * 400 + 7;
const int mod = (int)1e9 + 7;


int dp1[dd];
int dp2[dd];
int P[dd];
int S;

void add(int &a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

int sum(int l, int r) {
	l = max(l, 0);
	r = min(r, S);
	
	if (l > r) return 0;
	
	int res = P[r];
	if (l) add(res, mod - P[l - 1]);
	
	return res;
}

int main() {
	int n, k, p;
	cin >> n >> k >> p;
	
	if (n * k < p) return 0 * puts("0");
	
	dp1[0] = 1;
	
	for (int len = 1; len <= n; len++) {
		S = min(len * k + 1, p);
		for (int j = 0; j <= min(len * k + 1, p); j++) {
			P[j] = dp1[j];
			if (j) add(P[j], P[j - 1]);
		}
		for (int j = 0; j <= min(len * k + 1, p); j++) {
			if (k - 1 <= len - k) {
				int t = min(k - 2, j - 1);
				add(dp2[j], sum(j - (t + 1), j - 1));
				if (j >= k) add(dp2[j], 1ll * dp1[j - k] * ((len - k) - (k - 1) + 1) % mod);
				int x = max(len - k + 1, len - j);
				add(dp2[j], sum(j - (len - x), j - 1));
			} else if (len < k) {
				add(dp2[j], 1ll * dp1[j] * len % mod);
			} else {
				int t = len - k;
				add(dp2[j], sum(j - t, j - 1) * 2ll % mod);
				if (j >= (t + 1)) add(dp2[j], 1ll * (len - 2 * t) * dp1[j - (t + 1)] % mod);
			
			}
		}
		memcpy(dp1, dp2, sizeof(dp2));
		memset(dp2, 0, sizeof(dp2));
	}
	cout << dp1[p] << "\n";
	return 0;
}