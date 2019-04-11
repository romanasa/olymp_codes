#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 7;
const int LOG = 18;

struct FenwickTree {
	int T[dd];
	void upd(int pos, int val) { for (int i = pos + 1; i < dd; i += (i&-i)) T[i] += val; }
	int get(int pos) { int res = 0;	for (int i = pos + 1; i; i -= (i&-i)) res += T[i]; return res; }
	int get(int l, int r) { return get(r) - get(l - 1); }
} T;

#define TASK "occupation"

vector<vector<int> > E;
int h[dd], tin[dd], tout[dd], tmm;
int up[dd][LOG];
int used[dd];

bool par(int a, int b) { return tin[a] <= tin[b] && tout[b] <= tout[a]; }

void dfs(int v, int pr = -1) {
	h[v] = (pr == -1 ? 0 : h[pr] + 1);
	if (pr == -1) for (int i = 0; i < LOG; i++) up[v][i] = v;
	else {
		up[v][0] = pr;
		for (int i = 1; i < LOG; i++) up[v][i] = up[up[v][i - 1]][i - 1];
	}
	tin[v] = tmm++;
	for (int to : E[v]) if (to != pr) 
		dfs(to, v);
	tout[v] = tmm++;
}

int lca(int a, int b) {
	if (par(a, b)) return a;
	if (par(b, a)) return b;
	for (int i = LOG - 1; i >= 0; i--)
		if (!par(up[a][i], b)) a = up[a][i];
	return up[a][0];
}

set<pair<int, int> > S;

int calc(int v0, int t, int a) {
	//err("v0 = %d, t = %d, a = %d\n", v0, t, a);
	int cA = T.get(tin[a], tout[a]);
	int cT = T.get(tin[t], tout[t]);
	
	if (par(v0, t) && cA) return h[a] - h[t] + 1;
	if (par(v0, t) && cT && !cA) {
		int v = a;
		for (int i = LOG - 1; i >= 0; i--) {
			int to = up[v][i];
			if (T.get(tin[to], tout[to]) == 0) v = to;
		}
		v = up[v][0];
		return h[v] - h[t] + 1;
	}
	if (cT == 0) return 0;
	if (par(a, v0) && h[v0] > h[a]) return 0;
	if (par(t, v0) && cA) return h[a] - h[v0] + 1;
	if (par(t, v0) && cA == 0) {
		int v = a;
		for (int i = LOG - 1; i >= 0; i--) {
			int to = up[v][i];
			if (T.get(tin[to], tout[to]) == 0) v = to;
		}
		v = up[v][0];
		if (v == t) return 0;
		return h[v] - h[v0] + 1;
	}
	assert(0);
}

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	
	E.resize(n);
	
	for (int i = 0; i + 1 < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
	}
	
	dfs(0);
	
	int q;
	scanf("%d", &q);
	
	while (q--) {
		int t;
		scanf("%d", &t);
		if (t == 1) {
			int v;
			scanf("%d", &v);
			v--;
			if (used[v]) {
				T.upd(tin[v], -1);
				S.erase({ tin[v], v });
				S.erase({ tout[v], v });
			} else {
				T.upd(tin[v], 1);
				S.insert({ tin[v], v });
				S.insert({ tout[v], v });
			}
			used[v] ^= 1;
		} else {
			int a, b;
			scanf("%d %d", &a, &b);
			a--, b--;
			
			if (S.empty()) { printf("0\n"); continue; }
			
			int t = lca(a, b);
			int v0 = lca(S.begin()->second, S.rbegin()->second);
			
			int res = calc(v0, t, a) + calc(v0, t, b);
			//err("res = %d\n", res);
			if (par(v0, t) && T.get(tin[t], tout[t])) res--;
			printf("%d\n", res);
		}
	}
	
	return 0;
}