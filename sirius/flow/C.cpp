#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct edge { int to, c, f, back; };

vector<vector<edge> > E;

void add(int a, int b, int c) {
	int ia = (int)E[b].size();
	int ib = (int)E[a].size();
	E[a].push_back({ b, c, 0, ia });
	E[b].push_back({ a, 0, 0, ib });
}

int dfs(int v, int t, int cmin) {
	if (v == t) return cmin;
	used[v] = 1;
	for (auto &e : E[v]) {
		if (!used[e.to] && e.f < e.c) {
			int df = dfs(e.to, t, min(cmin, e.c - e.f));
			if (df) {
				e.f += df;
				E[e.to][e.back].f -= df;
				return df;
			}
		}
	}
	return 0;
}

int findflow(int s, int t) {
	int flow = 0;
	while (1) {
		int df = dfs(s, t, (int)1e9);
		if (!df) break;
		flow += df;
	}
	return flow;
}

int main() {
	int n, m, k, s, t;
	scanf("%d %d %d %d %d", &n, &m, &k, &s, &t);
	
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--, b--;
		add(a, b);
	}
	return 0;
}