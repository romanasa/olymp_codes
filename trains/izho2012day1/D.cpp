#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<int> > E;

const int dd = (int)2e5 + 1;

int dp[dd][507];
int cost[3][507];
int c[dd];

int n, m;

int calc(int v) {
	dp[v][0] = 0;
	dp[v][1] = c[v];
	
	int sz = 1;
	
	for (int to : E[v]) sz += calc(to);
	
	for (int j = 0; j <= min(m, sz); j++) cost[0][j] = cost[1][j] = -(int)1e9;
	
	cost[0][0] = 0;
	
	for (int i = 0; i < (int)E[v].size(); i++) {
		
		for (int j = 0; j <= min(m, sz); j++) if (cost[0][j] != -(int)1e9) {
			for (int t = 0; t <= min(m, sz); t++) {
				if (dp[E[v][i]][t] == -(int)1e9) break;
				cost[1][j + t] = max(cost[1][j + t], cost[0][j] + dp[E[v][i]][t]);
			}
		}	
		
		for (int j = 0; j <= min(m, sz); j++) {
			cost[0][j] = cost[1][j];
			cost[1][j] = -(int)1e9;
		}	
	}
	
	for (int j = 0; j <= min(m, sz); j++) {
		dp[v][j] = max(dp[v][j], cost[0][j]);
		//if (dp[v][j] != -(int)1e9) err("dp[%d][%d] = %d\n", v, j, dp[v][j]);
	}
	//err("\n");
	return sz;
}

#define TASK "d"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	cin >> n >> m;
	
	for (int i = 0; i < n; i++) fill(dp[i], dp[i] + m + 1, -(int)1e9);
	
	E.resize(n);
	int root = -1;
	
	for (int i = 0; i < n; i++) {
		int p;
		cin >> p >> c[i];
		if (p == 0) root = i;
		else E[p - 1].push_back(i); 
	}
	
	calc(root);
	cout << dp[root][m] << "\n";
	
	return 0;
}