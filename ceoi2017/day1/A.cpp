#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct edge { int first, second, id; };

vector<vector<edge> > E, G;

const int dd = (int)1e5 + 1;

int up[dd], tin[dd], tmm, used[dd];
int br[dd], comp[dd];
int L[dd], R[dd], S1[dd], S2[dd];

void dfs(int v, int pr) {
	used[v] = 1;
	tin[v] = up[v] = tmm++;
	
	for (auto c : E[v]) {
		if (pr == c.second) continue;
		int to = c.first;
		if (used[to]) {
			up[v] = min(up[v], tin[to]);
		} else {
			dfs(to, c.second);
			up[v] = min(up[v], up[to]);
			
			if (up[to] >= tin[to]) {
				br[c.second] = 1;
			}
		}
	}
}

void mark(int v, int col) {
	comp[v] = col;
	for (auto c : E[v]) {
		if (comp[c.first] == -1 && !br[c.second])
			mark(c.first, col);
	}
}

const int LOG = 17;
int U[LOG][dd];
int tout[dd];

bool par(int a, int b) { return tin[a] <= tin[b] && tout[b] <= tout[a]; }

void calc(int v, int pr = -1) {
	used[v] = 1;
	if (pr == -1) {
		for (int i = 0; i < LOG; i++) U[i][v] = v;
	} else {
		U[0][v] = pr;
		for (int i = 1; i < LOG; i++) U[i][v] = U[i - 1][U[i - 1][v]];
	}
	
	tin[v] = tmm++;
	for (auto c : G[v]) if (c.first != pr) {
		calc(c.first, v);
	}
	tout[v] = tmm++;
}

int lca(int a, int b) {
	for (int i = LOG - 1; i >= 0; i--) {
		if (!par(U[i][a], b)) a = U[i][a];
	}
	return a;
}

int P1[dd], P2[dd];

void ans(int v, int pr = -1) {
	err("in %d\n", v);
	used[v] = 1;
	
	for (auto c : G[v]) if (c.first != pr) {
		int t = c.first;
		
		ans(t, v);
	
		S1[t] += P1[t];
		S2[t] += P2[t];
		
		if (S1[t]) {
			err("%d-->%d UP\n", v, t);
			if (!c.id) L[c.second] = 1;
			else R[c.second] = 1;
		}
		S1[v] += S1[t];
		
		if (S2[t]) {
			if (c.id) L[c.second] = 1;
			else R[c.second] = 1;
		}
		S2[v] += S2[t];
	}
	err("out %d\n", v);
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	E.resize(n);
	
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		E[a - 1].push_back({ b - 1, i, 1 });
		E[b - 1].push_back({ a - 1, i, 0 });
	}
	
	for (int i = 0; i < n; i++) if (!used[i]) dfs(i, -1);
	
	fill(comp, comp + n, -1);
	int cur = 0;
	
	for (int i = 0; i < n; i++) if (comp[i] == -1) {
		mark(i, cur++);
	}
	
	for (int i = 0; i < n; i++) err("comp[%d] = %d\n", i, comp[i]);
	
	G.resize(cur);
	
	for (int v = 0; v < n; v++) {
		for (auto c : E[v]) if (br[c.second]) {
			G[comp[v]].push_back({ comp[c.first], c.second, c.id });
			err("%d----%d\n", comp[v], comp[c.first]);
		}
	}
	
	fill(tin, tin + cur, 0);
	fill(used, used + cur, 0);
	tmm = 1;
	
	for (int i = 0; i < cur; i++) if (!used[i]) calc(i);
	
	int q;
	scanf("%d", &q);
	
	for (int i = 0; i < q; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--, b--;
		
		int ca = comp[a], cb = comp[b];
		
		err("a = %d, b = %d, ca = %d, cb = %d\n", a, b, ca, cb);
		
		if (ca == cb) continue;
		
		if (!par(ca, cb)) {
			int pa = lca(ca, cb);
			pa = U[0][pa];
			P1[ca]++, P1[pa]--;
			err("ca = %d, cb = %d, pa = %d\n", ca, cb, pa);
		}
		
		if (!par(cb, ca)) {
			int pb = lca(cb, ca);
			pb = U[0][pb];
			err("ca = %d, cb = %d, pb = %d\n", ca, cb, pb);
			P2[cb]++, P2[pb]--;
		}
	}
	
	fill(used, used + cur, 0);
	for (int i = 0; i < cur; i++) if (!used[i]) ans(i);
	
	for (int i = 0; i < m; i++) {
		if (L[i] ^ R[i]) putchar(R[i] ? 'L' : 'R');
		else putchar('B');
	}
	putchar('\n');
	
	return 0;
}