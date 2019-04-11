#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = (int)1e9 + 7;

void add(int &a, int b) { a += b; if (a >= mod) a -= mod; }

int dp[107][(1 << 11) + 7];
int G[(int)1e4 + 7];

#define TASK "lcm"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ll n, k;
	cin >> n >> k;

	ll old = n;
	
	vector<pair<ll, ll> > T;
	
	for (ll i = 2; i * i <= n; i++) if (n % i == 0) {
		int p = 0;
		while (n % i == 0) 
			p++, n /= i;
		T.push_back({ i, p });
	}
	if (n > 1) T.push_back({ n, 1 });
	
	int len = (int)T.size();
	assert(len <= 11);
	
	n = old;
	vector<ll> divs;
	for (ll i = 1; i * i <= n; i++) if (n % i == 0) {
		divs.push_back(i);
		if (i * i != n) divs.push_back(n / i);
	}
	
	sort(divs.begin(), divs.end());
	
	for (int i = 0; i < (int)divs.size(); i++) {
		for (int j = 0; j < len; j++) {
			int pc = 0;
			ll x = divs[i];
			
			while (x % T[j].first == 0) x /= T[j].first, pc++;
			if (pc == T[j].second) G[i] |= (1 << j);
		}
	}
	//err("T = "); for (auto c : T) err("(%I64d, %I64d), ", c.first, c.second); err("\n");
	//err("divs = "); for (auto c : divs) err("%I64d, ", c); err("\n");
	
	dp[0][0] = 1;
	for (int x = 0; x < (int)divs.size(); x++) {
		for (int i = 0; i < k; i++) {
			for (int msk = 0; msk < (1 << len); msk++) {
				add(dp[i + 1][msk | G[x]], dp[i][msk]);
			}
		}
	}
	cout << dp[k][(1 << len) - 1] << "\n";
	
	return 0;
}