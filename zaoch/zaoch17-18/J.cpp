#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2007;

vector<vector<int> > E;
int pr[dd], prl[dd];
int used[dd], tmm;
int ans;

bool dfs(int v) {
	if (used[v] == tmm) return false;
	used[v] = tmm;
	
	for (int to : E[v]) {
		if (pr[to] == -1) {
			pr[to] = v;
			prl[v] = to;
			ans--;
			return true;
		}
	}
	
	for (int to : E[v]) {
		if (dfs(pr[to])) {
			pr[to] = v;
			prl[v] = to;
			return true;
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	E.resize(n);
	
	fill(pr, pr + 2 * n, -1);
	fill(prl, prl + 2 * n, -1);
	
	ans = n;
	
	for (int i = 0; i < m; i++) {
		
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		E[a].push_back(b + n);
		for (int run = 1; run; ) {
			run = 0;
			tmm++;
			for (int i = 0; i < n; i++) if (prl[i] == -1 && dfs(i)) {
				run = 1;
			}
		}
		cout << ans << " ";
	}
	return 0;
}