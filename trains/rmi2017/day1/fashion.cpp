#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e4 + 7;

struct edge {
	int to;
	ll f, c;
	int back;
};

vector<vector<edge> > E;

void add(int a, int b, ll c) {
	int ia = (int)E[b].size();
	int ib = (int)E[a].size();
	E[a].push_back({ b, 0, c, ia });
	E[b].push_back({ a, 0, 0, ib });
	//err("%d %d %I64d\n", a, b, c);
}

int N;
int used[3 * dd];

ll dfs(int v, int t, ll cmin) {
	if (v == t) return cmin;
	used[v] = 1;
	for (auto &e : E[v]) {
		if (!used[e.to] && e.f < e.c) {
			ll df = dfs(e.to, t, min(cmin, e.c - e.f));
			if (df) {
				e.f += df;
				E[e.to][e.back].f -= df;
				return df;
			}
		}
	}
	return 0;
}

ll findflow(int s, int t) {
	ll flow = 0;
	while (1) {
		fill(used, used + N, 0);
		ll df = dfs(s, t, 1e18);
		if (!df) break;
		flow += df;
	}
	return flow;
}

int t[dd], q[dd];
int a[dd], b[dd], c[dd], w[dd];
int ans[3 * dd];

void path(int v) {
	ans[v] = 1;
	for (auto &e : E[v]) if (e.f < e.c) {
		if (!ans[e.to]) path(e.to);
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	for (int i = 0; i < n; i++) scanf("%d %d", &t[i], &q[i]);
	for (int i = 0; i < m; i++) scanf("%d %d %d %d", &a[i], &b[i], &c[i], &w[i]);
	for (int i = 0; i < m; i++) a[i]--, b[i]--, c[i]--;
	
	N = n + m + 7;
	int s = n + m + 1;
	int t = n + m + 2;
	E.resize(N);
	
	for (int i = 0; i < n; i++) add(s, i, q[i]);
	
	for (int i = 0; i < m; i++) {
		add(a[i], n + i, 1e18);
		add(b[i], n + i, 1e18);
		add(c[i], n + i, 1e18);
		add(n + i, t, w[i]);
	}
	
	ll f = findflow(s, t);
	ll sumw = accumulate(w, w + m, 0ll);
	
	
	//for (auto &e : E[s]) if (e.c > 0 && e.f == e.c)
	//	ans[e.to] = 1;
		
	/*for (int i = 0; i < m; i++) {
	    for (auto &e : E[n + i]) {
	        if (e.c > 0 && e.f < e.c) ans[a[i]] = ans[b[i]] = ans[c[i]] = 1;
	    }
	}*/
	
	/*
	err("f = %I64d\n", f);
	for (int v = 0; v < N; v++) {
		for (auto &e : E[v]) if (e.c > 0) {
			err("%d--%I64d/%I64d-->%d\n", v, e.f, e.c, e.to); 
		}	
	}*/
	
	path(s);
	for (int i = 0; i < n; i++) ans[i] ^= 1;
	
	ll cost = 0;
	for (int i = 0; i < m; i++) if (ans[a[i]] && ans[b[i]] && ans[c[i]]) cost += w[i];
	for (int i = 0; i < n; i++) if (ans[i]) cost -= q[i];
	/*
	if (cost < 0) {
		puts("0 0");
		return 0;
	}*/
	//assert(sumw - f == cost);
	
	printf("%lld %d\n", sumw - f, accumulate(ans, ans + n, 0));
	for (int i = 0; i < n; i++) if (ans[i]) printf("%d ", i + 1);
	
	return 0;
}