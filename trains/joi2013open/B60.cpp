#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<pair<int, int> > > E;
vector<int> used, bl, t;
vector<pair<int, int> > edges;

void dfs(int v) {
	used[v] = 1;
	for (auto c : E[v]) {
		if (!used[c.first] && !bl[c.second]) dfs(c.first);
	}
}

int n, m, q;
	
int solve(int v) {
	bl.assign(n, 1), used.assign(n, 0);
	for (int i = 0; i < m; i++) bl[t[i]] ^= 1;
	
	dfs(v);
	for (int i = m - 1; i >= 0; i--) {
		bl[t[i]] ^= 1;
		if (bl[t[i]] == 0) {
			
			int a = edges[t[i]].first;
			int b = edges[t[i]].second;
		
			if (used[a] && !used[b]) dfs(b);
			if (used[b] && !used[a]) dfs(a);
		}
	}
	return accumulate(used.begin(), used.end(), 0);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q;
	
	E.resize(n);
	used.resize(n), edges.resize(n);
	t.resize(m);
	
	for (int i = 0; i + 1 < n; i++) {
		int a, b;
		cin >> a >> b;
		edges[i] = { a - 1 , b - 1 };
		E[a - 1].push_back({ b - 1, i });
		E[b - 1].push_back({ a - 1, i });
	}
	
	for (int i = 0; i < m; i++) {
		cin >> t[i]; t[i]--;
	}
	//err("ok\n");
	
	if (q == 1) {
    	while (q--) {
    		int v;
    		cin >> v;
    		cout << solve(v - 1) << "\n";
    	}
	} else {
		bl.assign(n, 0);
		
		vector<pair<int, int> > T(n);
		set<int> S;
		
		for (int i = 0; i < n; i++) S.insert(i);
		for (int i = 0; i < n; i++) T[i] = { i, i + 1 };
		
		for (int i = 0; i < m; i++) {
			int x = t[i] + 1;
			
			auto it = S.lower_bound(x);
			--it;
			
			if (bl[x] == 0) {
				S.erase(x);
				T[*it].second = T[x].second;
			} else {
				S.insert(x);
				T[x] = T[*it];
			}
			bl[x] ^= 1;
		}
		for (int i = 0; i < n; i++) {
			auto it = S.lower_bound(i + 1); --it;
			cout << T[*it].second - T[*it].first << "\n";
		}
		
	}
	
	return 0;
}