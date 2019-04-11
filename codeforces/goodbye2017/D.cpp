#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = (int)1e9 + 7;
const int dd = 2007;

int dp[dd][dd];
int k;

int add(int a, int b) {
	a += b;
	return a >= mod ? a - mod : a;
}

int mul(int a, int b) {
	return 1ll * a * b % mod;
}

int bp(int a, int n) {
	if (!n) return 1;
	if (n & 1) return mul(bp(a, n - 1), a);
	int t = bp(a, n / 2);
	return mul(t, t);
}

int inv(int x) {
	return bp(x, mod - 2);
}

int frac(int a, int b) {
	return mul(a, inv(b));
}

int pA, pB;

int calc(int n, int m) {
	if (m >= k) return m;
	
	if (n >= k) {
		int cur = add(n, m);
		return add(cur, frac(pA, pB));
	}
	
	if (dp[n][m] != -1) return dp[n][m];
	
	int res = add(mul(calc(n + 1, m), pA), mul(calc(n, n + m), pB));
	return dp[n][m] = res;
}

int main() {
	for (int i = 0; i < dd; i++) fill(dp[i], dp[i] + dd, -1);
		
	int pa, pb;
	cin >> k >> pa >> pb;

	pA = frac(pa, pa + pb);
	pB = frac(pb, pa + pb);

	cout << calc(1, 0) << "\n";
	
	return 0;
}