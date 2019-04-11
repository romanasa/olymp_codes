#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;
const int LOG = 20;

int used[dd];
int cost[dd][3][LOG + 2];
int dp[dd][2][LOG + 2];

vector<vector<int> > E, G;

void dfs(int v) {
	used[v] = 1;
	for (int to : E[v]) if (!used[to]) dfs(to);
}

void precalc(int v, int pr = -1) {
	for (int to : E[v]) if (to != pr) {
		G[v].push_back(to);
		precalc(to, v);
	}
}

int mod;

void add(int &a, int b) {
	a += b;
	if (a >= mod) a-= mod;
}

void calc(int v) {
	for (int to : G[v]) calc(to);
	
	for (int i = 0; i <= (int)G[v].size(); i++)
		for (int p = 0; p <= 2; p++)
			fill(cost[i][p], cost[i][p] + LOG + 2, 0);
			
	cost[0][0][0] = 1;
	
	for (int i = 0; i < (int)G[v].size(); i++) {
		for (int p = 0; p <= 2; p++) {
			for (int curK = 0; curK < LOG; curK++) if (cost[i][p][curK]) {
				for (int sunK = 0; sunK < LOG; sunK++) {
					for (int t = 0; t < 2; t++) if (p + t <= 2) {
						add(cost[i + 1][p + t][max(sunK + (t ^ 1), curK)], 1ll * cost[i][p][curK] * dp[G[v][i]][t][sunK] % mod); 
					}
				}
			}
		}
	}
	
	int sz = (int)G[v].size();
	for (int k = 0; k < LOG + 2; k++) {
		for (int j = 0; j <= 2; j++) {
			add(dp[v][0][k], cost[sz][j][k]);
			if (j != 2) add(dp[v][1][k], cost[sz][j][k]);
		}
	}
}

int main() {
	int n, m;
	cin >> n >> m >> mod;
	
	int old = mod;
	if (mod < 10) mod *= 1000;
	
	E.resize(n);
	G.resize(n);
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
	}
	
	dfs(0);
	if (*min_element(used, used + n) == 0) return 0 * puts("-1\n-1");
	
	precalc(0);
	calc(0);
	
	for (int k = 0; k < LOG; k++) {
		if (dp[0][0][k] > 0) {
			cout << k << "\n" << dp[0][0][k] % old << "\n";
			return 0;
		}
	}
	cout << "-1\n-1\n";
	
	
	return 0;
}