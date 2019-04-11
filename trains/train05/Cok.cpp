#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int dd = (int)107;

int used[dd], cnt;
vector<vector<int> > E;

void dfs(int v) {
	++cnt;
	used[v] = 1;
	for (int to : E[v]) {
		if (!used[to]) {
			dfs(to);
		}
	}
}

int main() {
	int n, k, d;
	scanf("%d %d %d", &n, &k, &d);
	
	vector<pair<int, int> > edges;
	
	for (int i = 0; i + 1 < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		edges.push_back({ a - 1, b - 1 });
	}
	int ans = 0;
	for (int msk = 0; msk < (1 << (n - 1)); msk++) {
		E.resize(0);
		E.resize(n);
		for (int i = 0; i + 1 < n; i++) {
			if ((msk >> i) & 1) {
				E[edges[i].first].push_back(edges[i].second);
				E[edges[i].second].push_back(edges[i].first);
			}
		}
		
		int mn = n, mx = 0;
		int cur = 0;
		
		memset(used, 0, sizeof(int) * n);
		for (int i = 0; i < n; i++) {
			if (!used[i]) {
				cnt = 0;
				dfs(i);
				mn = min(mn, cnt);
				mx = max(mx, cnt);
				cur++;
			}
		}
		if (mx - mn <= d && cur == k) ans++;
	}
	printf("%d\n", ans);
	return 0;
}