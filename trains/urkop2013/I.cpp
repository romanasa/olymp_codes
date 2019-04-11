#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

bitset<1007> m1[23], m2[23], cur1, cur2;
const int mod = 998244353;

int main() {
	int n, m;
	cin >> n >> m;
	
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		for (int j = 0; j < x; j++) {
			int t;
			cin >> t;
			if (t < 0) m1[i][-t - 1] = 1;
			else m2[i][t - 1] = 1;
		}
	}
	
	vector<int> p(n + 1);
	p[0] = 1;
	for (int i = 1; i <= n; i++) p[i] = 2 * p[i - 1] % mod;
	
	int ans = 0;
	for (int msk = 0; msk < (1 << m); msk++) {
		
		cur1.reset();
		cur2.reset();
		
		int cnt = 0;
		for (int i = 0; i < m; i++) if ((msk >> i) & 1) {
			cur1 |= m1[i];
			cur2 |= m2[i];
			cnt++;
		}
		
		if ((cur1 & cur2).count()) continue;
		
		int k = n - (cur1 | cur2).count();
		
		if (cnt % 2 == 0) ans += p[k];
		else ans -= p[k];
		
		if (ans >= mod) ans -= mod;
		if (ans < 0) ans += mod;
	}
	
	cout << ans << "\n";
	return 0;
}