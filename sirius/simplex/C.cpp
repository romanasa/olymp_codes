#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e4 + 7;

struct edge { int to, f, c, back, ind; };

vector<vector<edge> > E;

void add(int a, int b, int c, int ind) {
	 int ia = (int)E[b].size();
	 int ib = (int)E[a].size();
	 
	 E[a].push_back({ b, 0, c, ia, ind });
	 E[b].push_back({ a, 0, 0, ib, -1 });
}

int used[dd];

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

int N;

int findflow(int s, int t) {
	int flow = 0;
	while (1) {
		fill(used, used + N, 0);
		int df = dfs(s, t, (int)1e9);
		if (!df) break;
		flow += df;
	}
	return flow;
}

map<string, int> M;
int nv;


int get(string s) {
	if (M.count(s)) return M[s];
	return M[s] = nv++;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	N = n;
	E.resize(N);
	
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		add(a - 1, b - 1, c, i);
	}
	
	printf("%d\n", findflow(0, n - 1));
	
	vector<int> res(m);
	for (int v = 0; v < n; v++) {
		for (auto &e : E[v]) {
			if (e.ind >= 0) res[e.ind] = e.f;
		}
	} 
	
	for (int i = 0; i < m; i++) printf("%d ", res[i]);
	return 0;
}