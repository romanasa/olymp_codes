#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 7;

ll Q[dd];
int iG;

struct Fen {
	ll T[dd];
	//unordered_map<ll, ll> T;
	
	//Fen() { fill(T, T + dd, -1); }
	
	int check(ll x) {
		return lower_bound(Q, Q + iG, x) - Q;
	}
	
	void upd(ll pos, ll val) {
		for (int i = check(pos) + 1; i; i -= (i&-i)) T[i] = max(T[i], val);
	}
	
	ll get(ll pos) {
		ll res = 0;
		for (int i = check(pos) + 1; i < dd; i += (i&-i)) res = max(res, T[i]);
		return res;
	}
} F;

#define TASK "divide"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	vector<int> x(n + 1), d(n + 1), g(n + 1);
	vector<ll> D(n + 1), G(n + 1);
	
	for (int i = 1; i <= n; i++) {
		cin >> x[i] >> g[i] >> d[i];
		D[i] = D[i - 1] + d[i];
		G[i] = G[i - 1] + g[i];
	}
	
	for (int i = 1; i <= n; i++) {
		Q[iG++] = D[i - 1] - x[i];
		Q[iG++] = D[i] - x[i];
	}
	
	sort(Q, Q + iG);
	iG = unique(Q, Q + iG) - Q;
	
	ll ans = *max_element(g.begin() + 1, g.end());
	
	for (int i = n; i > 0; i--) {
		//err("i = %d\n", i);
		if (i < n) {
			ll cur = F.get(D[i - 1] - x[i]) - G[i - 1];
			ans = max(ans, cur);
		}
		F.upd(D[i] - x[i], G[i]);
		//err("ok\n");
	}
	cout << ans << "\n";
	return 0;
}