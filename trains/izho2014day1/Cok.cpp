#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<int> > E;
int d[531][531];
int used[531];

int dfs(int v, int t, int cur) {
	if (v == t) return cur == 0;
	
	int res = 0;
	
	used[v] = 1;
	
	for (int to : E[v]) if (!used[to]) {
		res += dfs(to, t, cur - 1);
	}	
	used[v] = 0;
	return res;
}

#define TASK "shymbulak"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	cin >> n;
	
	E.resize(n);
	
	for (int i = 0; i < n; i++) fill(d[i], d[i] + n, (int)1e9);
	for (int i = 0; i < n; i++) d[i][i] = 0;
	
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
		
		d[a - 1][b - 1] = 1;
		d[b - 1][a - 1] = 1;
	}
	
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}
	
	int minlen = 0;
	for (int i = 0; i < n; i++) for (int j = 0; j < i; j++) minlen = max(minlen, d[i][j]);
	
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (d[i][j] == minlen) {
				ans += dfs(i, j, minlen);
				//err("i = %d, j = %d\n", i, j);
			}
		}
	}
	
	cout << ans << "\n";
	
	return 0;
}