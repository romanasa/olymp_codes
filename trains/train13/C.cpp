#include <cstdio>
#include <vector>
#include <algorithm>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;

struct edge { int v, to, c; };

struct dsu {
	int P[dd], R[dd];
	dsu() { for (int i = 0; i < dd; i++) P[i] = i, R[i] = 1; }
	int get(int v) { return v == P[v] ? v : P[v] = get(P[v]); }
	void un(int a, int b) {
		a = get(a), b = get(b);
		if (a != b) {
			if (R[b] > R[a]) swap(a, b);
			P[b] = a, R[a] += R[b];
		}
	}
} J;

const int LOG = 17;

int used[dd];
int up[dd][LOG], mx[dd][LOG], mn[dd][LOG];
int h[dd];

vector<vector<pair<int, int>>>E;

void calc(int v, int pr, int len) {
	used[v] = 1;
	h[v] = (pr == -1 ? 0 : h[pr] + 1);
	
	if (pr == -1) {
		for (int i = 0; i < LOG; i++) up[v][i] = v, mx[v][i] = -1, mn[v][i] = (int)1e9 + 1;
	} else {
		up[v][0] = pr, mn[v][0] = mx[v][0] = len;
		for (int i = 1; i < LOG; i++) {
			up[v][i] = up[up[v][i - 1]][i - 1];
			mn[v][i] = min(mn[v][i - 1], mn[up[v][i - 1]][i - 1]);
			mx[v][i] = max(mx[v][i - 1], mx[up[v][i - 1]][i - 1]);
		}
	}
	for (auto &e : E[v]) {
		if (e.first != pr) {
			calc(e.first, v, e.second);
		}
	}
}

inline void uin(int &a, int b) { if (a > b) a = b; }
inline void uax(int &a, int b) { if (a < b) a = b; }


int getmin(int a, int b) {
	int cur = (int)1e9;
	
	err("a = %d, b = %d, ha = %d, hb = %d\n", a, b, h[a], h[b]);
	
	for (int i = LOG - 1; i >= 0; i--) if (h[up[a][i]] >= h[b]) 
		uin(cur, mn[a][i]), a = up[a][i];
		
	for (int i = LOG - 1; i >= 0; i--) if (h[up[b][i]] >= h[a]) 
		uin(cur, mn[b][i]), b = up[b][i];
	
	err("cur = %d\n", cur);
	if (a == b) return cur;
		
	for (int i = LOG - 1; i >= 0; i--) if (up[a][i] != up[b][i]) {
		uin(cur, min(mn[a][i], mn[b][i]));
		a = up[a][i], b = up[b][i];
	}
	uin(cur, min(mn[a][0], mn[b][0]));
	return cur;
}

int getmax(int a, int b) {
	int cur = -1;
	for (int i = LOG - 1; i >= 0; i--) if (h[up[a][i]] >= h[b]) 
		uax(cur, mx[a][i]), a = up[a][i];
	for (int i = LOG - 1; i >= 0; i--) if (h[up[b][i]] >= h[a]) 
		uax(cur, mx[b][i]), b = up[b][i];
	
	if (a == b) return cur;
		
	for (int i = LOG - 1; i >= 0; i--) if (up[a][i] != up[b][i]) {
		uax(cur, max(mx[a][i], mx[b][i]));
		a = up[a][i], b = up[b][i];
	}
	uax(cur, max(mx[a][0], mx[b][0]));
	return cur;
}

#define TASK "cycle"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, m;
	scanf("%d %d", &n, &m);
	
	E.resize(n);
	
	vector<edge> edges;
	vector<int> U(m);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		edges.push_back({ a - 1, b - 1, c });
	}
	
	sort(edges.begin(), edges.end(), [](edge a, edge b) { return a.c > b.c; });
	
	for (int i = 0; i < m; i++) {
		if (J.get(edges[i].v) != J.get(edges[i].to)) {
			err("i = %d, edge = (%d--%d--->%d)\n", i, edges[i].v, edges[i].c, edges[i].to);
			J.un(edges[i].v, edges[i].to);
			E[edges[i].v].push_back({ edges[i].to, edges[i].c });
			E[edges[i].to].push_back({ edges[i].v, edges[i].c });
			U[i] = 1;
		}		
	}
	
	for (int i = 0; i < n; i++) if (!used[i]) calc(i, -1, -1);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			err("mn[%d][%d] = %d; ", i, j, mn[i][j]);
		}
		err("\n");
		for (int j = 0; j < 2; j++) {
			err("up[%d][%d] = %d; ", i, j, up[i][j]);
		}
		err("\n");
	}
	
	err("calc\n");
	int ans = 0;
	for (int i = 0; i < m; i++) if (!U[i]) {
		int mn = min(getmin(edges[i].v, edges[i].to), edges[i].c);
		int mx = max(getmax(edges[i].v, edges[i].to), edges[i].c);
		ans = max(ans, mn + mx);
		err("i = %d, edge = (%d--%d--->%d)\n", i, edges[i].v, edges[i].c, edges[i].to);
		err("mn = %d, mx = %d\n", mn, mx);
	}
	printf("%d\n", ans);
	return 0;
}