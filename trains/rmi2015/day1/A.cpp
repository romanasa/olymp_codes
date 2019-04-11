#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct frac {
	ll a = 0, b = 1;
	
	void norm() {
		ll t = __gcd(a, b);
		a /= t, b /= t;
	}
	
	frac() {}
	frac(ll _a, ll _b) {
		a = _a, b = _b;
		norm();	
	}
	
	frac operator + (frac X) { 
		if (b > X.b) {
			assert(b % X.b == 0);
			return frac(a + X.a * (b / X.b), b);
		}
		assert(X.b % b == 0);
		return frac(a * (X.b / b) + X.a, X.b);
	}
	
	void div() { 
		if (a & 1) b *= 2;
		else a /= 2;
	}
};

const int dd = (int)307;
ll p[dd][dd];

#define TASK "spoiler"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, k;
	cin >> n >> k;
	
	int C = (n + 1) / 2;
	int x = k - C;
	
	for (int game = k - 1; game >= 0; game--) {
		for (int a = 0; a <= game - a; a++) {
			int b = game - a;
			
			if ((a == C - 1 && b < x) || (a == x && b > x)) {
				dp[game][a] = dp[game + 1][a];
			} else if ((b == C - 1 && a < x) || (b == x && a > x)) {
				dp[game][a] = dp[game + 1][a + 1];
			} else {
				dp[game][a] = dp[game + 1][a + 1] + dp[game + 1][a];
				dp[game][a].div();
				dp[game][a] = dp[game][a] + frac(1, 1);
			}
		}
	}
	cout << dp[0][0].a << "\n" << dp[0][0].b << "\n";
	return 0;
}