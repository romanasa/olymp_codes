#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int n, m;
int cnt = 0;
int ans = 0;

void go(int v, int cur, int x) {	
	if (cur % x) return;
	if (v == 0) {
		cnt++;
	} else {
		for (int i = 1; i <= m; i++) {
			go(v - 1, __gcd(cur, i), x);
		}
	}
}

const int mod = (int)1e9 + 7;

int bp(int a, int n) {
	if (n == 0) return 1;
	if (n & 1) return 1ll * bp(a, n - 1) * a % mod;
	int t = bp(a, n / 2);
	return 1ll * t * t % mod;
}

#define TASK "gcd"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	string s;
	cin >> s;

	int n = 0;	
	
	for (char c : s) {
		n = (1ll * n * 10 + c - '0') % (mod - 1);
	}
	
	
	int m;
	cin >> m;
	
	vector<int> T;
	for (int i = 1; i * i <= m; i++) {
		T.push_back(i);
		T.push_back(m / i);
	}
	
	sort(T.begin(), T.end());
	
	int ans = bp(m, n);
	
	for (int i = 0; i + 1 < (int)T.size(); i++) {
	
		int cur = bp(m / T[i + 1], n);
		int nxt = (i + 1 < (int)T.size() ? T[i + 1] : T[i] + 1);
		
		ans += 1ll * (nxt - T[i]) * cur % mod;
		if (ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}