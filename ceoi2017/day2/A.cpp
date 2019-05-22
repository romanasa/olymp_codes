#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e6 + 1;

int h[dd], w[dd];
ll dp[dd], s[dd];

struct line {
	ll k, b;
	int ind;
};

struct hull {
	vector<line> T;
	vector<double> G;

	void clear() { T.clear(), G.clear(); }

	void add(line Q) {
		while (T.size()) {
			if (T.back().k == Q.k) {
				if (T.back().b < Q.b) return;
				else T.pop_back(), G.pop_back();
			} else {
				double x = (Q.b - T.back().b) * 1.0 / (T.back().k - Q.k);
				if (x < G.back()) T.pop_back(), G.pop_back();
				else {
					T.push_back(Q), G.push_back(x);
					return;
				}
			}
		}
		T.push_back(Q);
		G.push_back(-(ll)1e18);
	}

	ll get(ll x) {	
		int j = upper_bound(G.begin(), G.end(), x) - G.begin() - 1;
		return T[j].k * x + T[j].b;
	}
} J;

void go(int l, int r) {
	if (l + 1 >= r) return;
	
	int m = (l + r) / 2;
	go(l, m);
	vector<line> cur;
	for (int j = l; j < m; j++) cur.push_back({ -2 * h[j], dp[j] - s[j + 1] + 1ll * h[j] * h[j]});
	
	sort(cur.begin(), cur.end(), [](line a, line b) { return a.k > b.k; } );
	
	J.clear();
	for (auto m : cur) J.add(m);
	for (int i = m; i < r; i++) dp[i] = min(dp[i], J.get(h[i]) + s[i] + 1ll * h[i] * h[i]);
	
	go(m, r);
}

int main() {
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) scanf("%d", &h[i]);
	for (int i = 0; i < n; i++) scanf("%d", &w[i]);
	for (int i = 0; i < n; i++) s[i + 1] = s[i] + w[i];
	
	dp[0] = 0;	
	for (int i = 1; i < n; i++) dp[i] = (ll)1e18;

	go(0, n);
	
	printf("%lld\n", dp[n - 1]);
	return 0;
}