#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int getmod(ll x, int mod) {
	if (x >= 32) return 32 + (x - 32) % mod;
	return x;
}

int phi(int n) {
	int res = n;
	for (int i = 2; i * i <= n; i++) if (n % i == 0) {
		while (n % i == 0) n /= i;
		res -= res / i;
	}
	if (n > 1) res -= res / n;
	return res;
}

vector<int> G;

int bp(int a, int n, int mod) {
	if (n == 0) return 1;
	if (n % 2) return getmod(1ll * bp(a, n - 1, mod) * a, mod);
	int t = bp(a, n / 2, mod);
	return getmod(1ll * t * t, mod);
}

int main() {
	//cout << phi(100) << "\n";
	//return 0;
	int n, m;
	cin >> n >> m;
	
	
	
	G.push_back(m);
	while (m > 1) m = phi(m), G.push_back(m);
	
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	
	int q;
	cin >> q;
	
	while (q--) {
		int l, r;
		cin >> l >> r;
		l--, r--;
		r = min(r, l + (int)G.size() - 1);
		int ans = 1;
		for (int j = r; j >= l; j--) {
			
			int x = ans;
			
			if (x >= 32) {
				//ans = 1;
				ans = bp(a[j], getmod(j - l + 1 < (int)G.size() ? G[j - l + 1] : 0, G[j - l + 1]), G[j - l]);
				cout << "===" << ans << "\n";
			} else ans = 1;
			
			ans = getmod(1ll * ans * bp(a[j], x, G[j - l]), G[j - l]);
		
			//cout << ans << "\n";
		}
		cout << ans % G[0] << "\n";
	}

	return 0;
}