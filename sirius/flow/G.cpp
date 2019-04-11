#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e3 + 7;

struct edge { int to, c, f, back; };

vector<vector<edge> > E;
int used[dd];
int h[dd];
int cnt[dd][dd];

void add(int a, int b, int c) {
	//err("add (%d, %d, %d)\n", a, b, c);
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


int n, low, high, m;

int findflow(int s, int t) {
	int flow = 0;
	while (1) {
		fill(used, used + n, 0);
		int df = dfs(s, t, (int)1e9);
		if (!df) break;
		flow += df;
	}
	return flow;
}


int main() {
	scanf("%d %d %d %d", &n, &low, &high, &m);
	low--, high--;
	
	for (int i = 0; i < m; i++) {
		scanf("%d", &h[i]);
		h[i]--;
	}
	
	if (*max_element(h, h + m) <= high) return 0 * puts("0");
	if (*min_element(h, h + m) >= low) return 0 * puts("0");
	
	for (int i = 0; i + 1 < m; i++) cnt[h[i]][h[i + 1]]++, cnt[h[i + 1]][h[i]]++;
	
	E.resize(n);
	
	int s = low - 1;
	int t = high + 1;
	
	for (int i = low; i <= high; i++) {
		int cur1 = 0;
		for (int j = 0; j < low; j++) cur1 += cnt[i][j];
		if (cur1) add(s, i, cur1);
		
		for (int j = low; j <= high; j++) if (cnt[i][j])
			add(i, j, cnt[i][j]);
			
		int cur2 = 0;
		for (int j = high + 1; j < n; j++) cur2 += cnt[i][j];
		if (cur2) add(i, t, cur2);
	}
	
	int cur = 0;
	for (int i = 0; i < low; i++)
		for (int j = high + 1; j < n; j++)
			cur += cnt[i][j];
	if (cur) add(s, t, cur);
	
	printf("%d\n", findflow(s, t));
	return 0;
}