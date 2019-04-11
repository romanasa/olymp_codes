#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

#define TASK "marriage"

vector<vector<int> > E;

const int dd = (int)3e4 + 7;

int cnt = 0, tmm;
int pr[2 * dd], used[2 * dd];

bool dfs(int v) {
	if (used[v] == tmm) return false;
	used[v] = tmm;
	for (int to : E[v]) if (pr[to] == -1) {
		pr[to] = v, pr[v] = to;
		cnt++;
		return true;
	}
	for (int to : E[v]) if (dfs(pr[to])) {
		pr[to] = v, pr[v] = to;
		return true;
	}
	return false;
}

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	E.resize(n);
	
	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		E[a - 1].push_back(b - 1 + n);
	}
	
	ll ans = 0;
	int r = 0;
	
	fill(pr, pr + n + m, -1);
	
	for (int l = 0; l < n; l++) {
	
		for (int r = l; r < n; r++) {
			cnt = 0;
			fill(pr, pr + n + m, -1);
			
			for (int j = l; j <= r; j++) tmm++, dfs(j);
			if (cnt == m) ans++;
		}
	}
	
	cout << ans << "\n";
	return 0;
}