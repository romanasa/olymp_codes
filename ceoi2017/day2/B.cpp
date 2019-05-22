#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int p = 31;
const int mod = (int)8e8 + 7;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	while (t--) {
		string s;
		cin >> s;
		
		int n = (int)s.size();
		
		vector<int> H(n + 1), P(n + 1);
		
		P[0] = 1;
		
		for (int i = 0; i < n; i++) {
			H[i + 1] = (1ll * H[i] * p + s[i] - 'a' + 1) % mod;
			P[i + 1] = 1ll * P[i] * p % mod;
		}
		
		int l = 0, r = n - 1;
		int ans = 0;
		
		auto get = [&H,&P](int l, int r) {
			int cur = H[r + 1] - 1ll * H[l] * P[r - l + 1] % mod;
			if (cur < 0) cur += mod;
			return cur;
		};
		
		while (l <= r) {	
			int cur = 0;
			while (l + cur < r - cur && get(l, l + cur) != get(r - cur, r)) {
				cur++;
			}
			ans++;
			if (l + cur < r - cur) ans++;
			cur++;
			l += cur, r -= cur;
		}
		cout << ans << "\n";
	}
	return 0;
}