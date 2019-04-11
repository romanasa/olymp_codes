#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

map<pair<ll, ll>, int> M[33];
ll C[33];
ll T[6], ans[6];

const int p = 239017;
const int mod = (int)1e9 + 7;
const int mod2 = (int)1e9 + 11;

#define TASK "high"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		
		for (int msk = 0; msk < 32; msk++) {
			ll h1 = 0, h2 = 0;
			for (int i = 0; i < 5; i++) if ((msk >> i) & 1) 
				h1 = (h1 * p + s[i]) % mod, h2 = (h2 * p + s[i]) % mod2;
			M[msk][{ h1, h2 }]++;
		}
	}
	
	for (int msk = 0; msk < 32; msk++) {
		for (auto c : M[msk]) C[msk] += 1ll * c.second * (c.second - 1) / 2;
	}
	
	for (int msk = 0; msk < 32; msk++) {
		T[__builtin_popcount(msk)] += C[msk];
	}
	
	//for (int i = 0; i <= 5; i++) err("T[%d] = %I64d\n", i, T[i]);
	
	ans[5] = T[5];
	ans[4] = T[4] - 5 * ans[5];
	ans[3] = T[3] - 4 * ans[4] - 10 * ans[5];
	ans[2] = T[2] - 3 * ans[3] - 6 * ans[4] - 10 * ans[5];
	ans[1] = T[1] - 2 * ans[2] - 3 * ans[3] - 4 * ans[4] - 5 * ans[5];
	ans[0] = T[0] - ans[1] - ans[2] - ans[3] - ans[4] - ans[5];
	for (int i = 0; i < 6; i++) cout << ans[5 - i] << " "; cout << "\n";
	return 0;
}