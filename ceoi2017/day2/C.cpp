#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;
const int maxV = 100 + 1;

vector<vector<int> > E;
int p[dd], n, k;
ll dp[dd][maxV], s[dd];
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


void upd(pair<pair<ll, int>, pair<ll, int> > &cur, ll val, int ind) {
	if (val >= cur.first.first) {
		cur.second = cur.first;
		cur.first = { val, ind }; 
	} else if (val >= cur.second.first) {
		cur.second = { val, ind }; 
	}
}
		
void calc(int v, int pr, vector<ll> &par) {
	

	//err("v = %d, ", v); if (pr != -1) for (int i = 0; i <= k; i++) err("%I64d, ", par[i]); err("\n");

	vector<pair<pair<ll, int>, pair<ll, int> > > cur(k + 1);
	
	cur[0] = { { 0, -1 }, { -1, -1 } };
	for (int j = 1; j <= k; j++) cur[j] = { { -1, -1 }, { -1, -1 } };
	
	for (int j = 1; j <= k; j++) {
		for (int to : E[v]) if (to != pr) {
			ll val = dp[to][j];
			if (dp[to][j - 1] != -1) {
				val = max(val, dp[to][j - 1] + s[to] - p[v]);
			}
			upd(cur[j], val, to);
		}
	}
	
	if (pr != -1) {
		for (int j = 1; j <= k; j++) {
			ll val = par[j];
			if (par[j - 1] != -1) {
				val = max(val, par[j - 1] + s[pr] - p[v]);
			}
			upd(cur[j], val, pr);
		}
	}
	
	for (int j = 0; j <= k; j++) {
		ans = max(ans, cur[j].first.first + (j == k ? 0 : s[v]));
	}
		
	for (int to : E[v]) if (to != pr) {
		vector<ll> curt(k + 1, -1);
		curt[0] = 0;
		for (int j = 1; j <= k; j++) curt[j] = (cur[j].first.second == to ? cur[j].second.first : cur[j].first.first);
		calc(to, v, curt);
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
	vector<ll> Q;
	calc(0, -1, Q);
		
	printf("%lld\n", ans);	
	return 0;
}