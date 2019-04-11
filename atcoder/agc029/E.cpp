#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

vector<vector<int>> E;
vector<int> pr, m;
vector<map<int, ll> > dp;
vector<ll> ans;

void dfs(int v) {
	for (int to : E[v]) if (to != pr[v]) {
		pr[to] = v;
		dfs(to);
	}
}

ll Q(int v, int x) {
	ll &cur = dp[v][x];
	if (cur > 0) return cur - 1;
	
	cur = 0;
	for (int to : E[v]) if (to != pr[v] && to < x) {
		cur += Q(to, x) + 1;
	}
	cur++;
	return cur - 1;
}

void calc(int v) {
	if (pr[v] == -1) {
		ans[v] = 1;
		m[v] = pr[v];
	} else {
		m[v] = max(pr[v], m[pr[v]]);
		ans[v] = ans[pr[v]];
		if (v > m[pr[v]]) ans[v] += Q(v, m[v]) + 1;
		else ans[v] += Q(v, m[v]) - Q(v, m[pr[v]]);
	}
	for (int to : E[v]) if (to != pr[v])
		calc(to);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n; cin >> n;
	dp.resize(n), pr.resize(n, -1), E.resize(n), ans.resize(n), m.resize(n);
	
	for (int i = 0; i + 1 < n; i++) {
		int a, b;
		cin >> a >> b;
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
	}
	dfs(0);
	calc(0);
	for (int v = 1; v < n; v++) cout << ans[v] - 1 << " \n"[v == n - 1];
	return 0;
}
