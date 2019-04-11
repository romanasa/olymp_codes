#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;


namespace GeneralMatching {
	const int MAXN = 307;
	int n;
	vector<int> g[MAXN];
	int match[MAXN], p[MAXN], base[MAXN], q[MAXN];
	bool used[MAXN], blossom[MAXN];
	
	int lca(int a, int b) {
		bool used[MAXN] = { 0 };
		for (;;) {
			a = base[a];
			used[a] = true;
			if (match[a] == -1) break;
			a = p[match[a]];
		}
		for (;;) {
			b = base[b];
			if (used[b]) return b;
			b = p[match[b]];
		}
	}
	
	void mark_path(int v, int b, int children) {
		while (base[v] != b) {
			blossom[base[v]] = blossom[base[match[v]]] = true;
			p[v] = children;
			children = match[v];
			v = p[match[v]];
		}
	}
	
	int find_path(int root) {
		memset(used, 0, sizeof(used));
		memset(p, -1, sizeof(p));
		for (int i = 0; i < n; i++) base[i] = i;
		
		used[root] = true;
		int qh = 0, qt = 0;
		q[qt++] = root;
		while (qh < qt) {
			int v = q[qh++];
			for (int i = 0; i < (int)g[v].size(); i++) {
				int to = g[v][i];
				if (base[v] == base[to] || match[v] == to) continue;
				if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
					int curbase = lca(v, to);
					memset(blossom, 0, sizeof(blossom));
					mark_path(v, curbase, to);
					mark_path(to, curbase, v);
					for (int i = 0; i < n; i++) {
						if (blossom[base[i]]) {
							base[i] = curbase;
							if (!used[i]) {
								used[i] = true;
								q[qt++] = i;
							}
						}
					}
				} else if (p[to] == -1) {
					p[to] = v;
					if (match[to] == -1) return to;
					to = match[to];
					used[to] = 1;
					q[qt++] = to;
				}
			}
		}
		return -1;
	}
	
	vector<pair<int, int>> solve(int _n, vector<pair<int, int>> edges) {
		n = _n;
		for (int i = 0; i < n; i++) g[i].clear();
		for (auto c : edges) {
			g[c.first].push_back(c.second);
			g[c.second].push_back(c.first);
		}
		memset(match, -1, sizeof(match));
		for (int i = 0; i < n; i++) {
			if (match[i] == -1) {
				int v = find_path(i);
				while (v != -1) {
					int pv = p[v], ppv = match[pv];
					match[v] = pv, match[pv] = v;
					v = ppv;
				}
			}
		}
		
		vector<pair<int, int>> ans;
		for (int i = 0; i < n; i++) if (match[i] > i)
			ans.emplace_back(i, match[i]);
		return ans;
	}
};

void solve() {
	int n, m;
	cin >> n >> m;
	vector<string> A(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	
	vector<pair<int, int>> edges;
	for (int i = 0; i < n; i++) {
		edges.emplace_back(i, i + n + m);
		for (int j = 0; j < m; j++) if (A[i][j] == '1') {
			edges.emplace_back(i, j + n);
			edges.emplace_back(i + n + m, j + n);
		}
	}
	auto t = GeneralMatching::solve(n + m + n, edges);
	cout << (int)t.size() - n << "\n";	
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
	return 0;
}