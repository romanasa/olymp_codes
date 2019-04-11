#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 7;
const int LOG = 18;

struct SegmentTree {
	pair<int, int> T[4 * dd];
	int P[4 * dd];
	
	void build(int v, int tl, int tr) {
		if (tl == tr) T[v] = { 0, tl };
		else {
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm);
			build(v * 2 + 1, tm + 1, tr);
			T[v] = max(T[v * 2], T[v * 2 + 1]);
		}
	}
	
	void upd(int v, int tl, int tr, int l, int r, int val) {
		if (tl == l && tr == r) T[v].first += val, P[v] += val;
		else {
			int tm = (tl + tr) / 2;
			if (r <= tm) upd(v * 2, tl, tm, l, r, val);
			else if (l > tm) upd(v * 2 + 1, tm + 1, tr, l, r, val);
			else upd(v * 2, tl, tm, l, tm, val), upd(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
			T[v] = max(T[v * 2], T[v * 2 + 1]);
			T[v].first += P[v];
		}
	}
} T;

int up[LOG][dd];
int tin[dd], tout[dd], tmm;
vector<int> leaf, ind;
pair<int, int> go[dd];
vector<vector<int> > E;

void dfs(int v, int pr = -1) {
	if (pr == -1) {
		for (int i = 0; i < LOG; i++) up[i][v] = v;
	} else {
		up[0][v] = pr;
		for (int i = 1; i < LOG; i++) up[i][v] = up[i - 1][up[i - 1][v]];
	}
	tin[v] = tmm++;
	
	if ((int)E[v].size() == 1) {
		leaf.push_back(tin[v]);
		ind.push_back(v);
	}
	
	for (int to : E[v]) if (to != pr) {
		dfs(to, v);
	}
	tout[v] = tmm++;
}

bool par(int a, int b) {
	return tin[a] <= tin[b] && tout[b] <= tout[a];
}

int get(int a, int b) {
	for (int i = LOG - 1; i >= 0; i--) {
		if (!par(up[i][a], b)) a = up[i][a];
	}
	return a;
}

int lca(int a, int b) {
	if (par(a, b)) return a;
	if (par(b, a)) return b;
	return up[0][get(a, b)];
}

vector<pair<pair<int, int>, int> > R[dd];

int main() {
	int n;
	scanf("%d", &n);
	
	//assert(n > 2);
	
	E.resize(n);
	for (int i = 0; i + 1 < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
	}
	
	int root = 0;
	for (int i = 0; i < n; i++) {
		if ((int)E[i].size() > 1) root = i;
	}
	dfs(root);
	
	for (int i = 0; i < n; i++) {
		int iL = lower_bound(leaf.begin(), leaf.end(), tin[i]) - leaf.begin();
		int iR = upper_bound(leaf.begin(), leaf.end(), tout[i]) - 1 - leaf.begin();
		go[i] = { iL, iR };
		//err("go[%d] = (%d, %d)\n", i, go[i].first, go[i].second);
	}
	
	int m;
	scanf("%d", &m);
	
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		a--, b--;

		if (par(b, a)) swap(a, b);
		
		int t = lca(a, b);
		
		if (a == t) {
			int x = get(b, a);
			
			R[0].push_back({ go[b], c });
			R[go[x].first].push_back({ go[b], -c });
			R[go[x].second + 1].push_back({ go[b], c });
			
			R[go[b].first].push_back({ { 0, (int)leaf.size() - 1}, c });
			R[go[b].first].push_back({ go[x], -c });
			
			R[go[b].second + 1].push_back({ { 0, (int)leaf.size() - 1 }, -c });
			R[go[b].second + 1].push_back({ go[x], c });
			
		} else {
			R[go[a].first].push_back({ go[b], c });
			R[go[a].second + 1].push_back({ go[b], -c });
			
			swap(a, b);
			
			R[go[a].first].push_back({ go[b], c });
			R[go[a].second + 1].push_back({ go[b], -c });
		}
	}
	
	vector<int> cur((int)leaf.size());
	
	T.build(1, 0, (int)leaf.size() - 1);
	
	int ans = 0, v = -1, to = -1;
	for (int i = 0; i < (int)leaf.size(); i++) {
		for (auto c : R[i])
			T.upd(1, 0, (int)leaf.size() - 1, c.first.first, c.first.second, c.second);
		auto cc = T.T[1];
		int val = cc.first;
		int ind = cc.second;
		if (val > ans) {
			ans = val, v = i, to = ind;
		}	
	}
	printf("%d %d %d\n", ind[v] + 1, ind[to] + 1, ans);
	return 0;
}