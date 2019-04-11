#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<int> > E;

const int dd = (int)2e5 + 1;

int c[dd];
int n, m;

#define TASK "d"

int dfs(int a, int b) {
	if (a == b) return true;
	for (int to : E[a]) {
		if (dfs(to, b)) return true;
	}
	return false;
}

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	cin >> n >> m;
	
	E.resize(n);
	int root = -1;
	
	for (int i = 0; i < n; i++) {
		int p;
		cin >> p >> c[i];
		if (p == 0) root = i;
		else E[p - 1].push_back(i); 
	}
	
	int ans = -(int)1e9;
	
	for (int msk = 0; msk < (1 << n); msk++) {
		
		vector<int> cur;
		int cost = 0;
		for (int i = 0; i < n; i++) if ((msk >> i) & 1)
			cur.push_back(i), cost += c[i];
			
		if ((int)cur.size() != m) continue;
		
		int ok = 1;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < m; j++) if (i != j)
				if (dfs(cur[i], cur[j])) ok = 0;
				
		if (ok) ans = max(ans, cost);
	}
	cout << ans << "\n";
	
	return 0;
}