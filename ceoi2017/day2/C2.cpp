#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;
const int maxV = 100 + 1;

vector<vector<int> > E;
int p[dd], n, k;
ll dp[dd][maxV], dp2[dd][maxV], s[dd];
ll ans;


void dfs(int v, int pr = -1) {
	fill(dp[v], dp[v] + k + 1, -1);
	
	dp[v][0] = 0;
	
	for (int to : E[v]) if (to != pr) {
		dfs(to, v);
	}
	for (int j = 1; j <= k; j++) {
		for (int to : E[v]) if (to != pr) {
			if (dp[to][j - 1] != -1) dp[v][j] = max(dp[v][j], dp[to][j - 1] + s[to] - p[v]);
			dp[v][j] = max(dp[v][j], dp[to][j]);
		}
	}
}

void calc(int v, int pr, vector<ll> par) {

	//err("v = %d, ", v); if (pr != -1) for (int i = 0; i <= k; i++) err("%I64d, ", par[i]); err("\n");


	vector<ll> cur(k + 1, -1);
	vector<multiset<ll> > Q(k + 1);
	
	cur[0] = 0;
	
	for (int j = 1; j <= k; j++) {
		for (int to : E[v]) if (to != pr) {
			cur[j] = max(cur[j], dp[to][j]);
			Q[j].insert(dp[to][j]);
			
			if (dp[to][j - 1] != -1) {
				cur[j] = max(cur[j], dp[to][j - 1] + s[to] - p[v]);
				Q[j].insert(dp[to][j - 1] + s[to] - p[v]);
			}
		}
	}
	
	if (pr != -1) {
		for (int j = 1; j <= k; j++) {
			cur[j] = max(cur[j], par[j]);
			Q[j].insert(par[j]);
			
			if (par[j - 1] != -1) {
				cur[j] = max(cur[j], par[j - 1] + s[pr] - p[v]);
				Q[j].insert(par[j - 1] + s[pr] - p[v]);
			}
		}
	}
	
	for (int j = 0; j <= k; j++) {
		ans = max(ans, cur[j] + (j == k ? 0 : s[v]));
	}
	
	for (int to : E[v]) if (to != pr) {
		
		vector<ll> curt(k + 1, -1);
		curt[0] = 0;
	
		for (int j = 1; j <= k; j++) {
			Q[j].erase(Q[j].find(dp[to][j]));
			if (dp[to][j - 1] != -1) {
				Q[j].erase(Q[j].find(dp[to][j - 1] + s[to] - p[v]));
			}
		} 
		
		for (int j = 1; j <= k; j++) curt[j] = (Q[j].size() ? *Q[j].rbegin() : -1);
		
		calc(to, v, curt);
		
		for (int j = 1; j <= k; j++) {
			Q[j].insert(dp[to][j]);
			if (dp[to][j - 1] != -1) {
				Q[j].insert(dp[to][j - 1] + s[to] - p[v]);
			}
		}
	}
}

int main() {
	scanf("%d %d", &n, &k);
	
	E.resize(n);
	
	for (int i = 0; i < n; i++) scanf("%d", &p[i]);
	
	for (int i = 0; i + 1 < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
		s[a - 1] += p[b - 1];
		s[b - 1] += p[a - 1];
	}
	
	dfs(0);
	calc(0, -1, vector<ll>(0));
		
	printf("%lld\n", ans);	
	return 0;
}