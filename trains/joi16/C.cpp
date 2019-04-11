#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 2e5 + 7;
int good[dd], d[dd], used[dd];
int ok[dd];
int n, m, q;

struct dsu {
	int R[dd], P[dd];
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

vector<vector<int>> E;

void bfs() {
	queue<int> q;
	q.push(0);
	
	fill(d, d + n, (int)1e9);
	d[0] = 0;
	
	while (q.size()) {
		int v = q.front();
		q.pop();
		for (int to : E[v]) if (d[to] > d[v] + 1) {
			d[to] = d[v] + 1, q.push(to);
		}
	}
}

int comp[dd], cnt[dd];

void dfs(int v, int c) {
	comp[v] = c;
	cnt[c]++;
	for (int to : E[v]) if (comp[to] == -1)
		dfs(to, c);
}

void init() {
	for (int i = 0; i < n; i++) E[i].clear();
}

int add(int a, int b) {
	if (d[a] == d[b]) return 0;
	E[a].push_back(b);
	
	int cur = 0;
	if (ok[a]) {
		queue<int> q;
		q.push(b);
		while (q.size()) {
			int v = q.front();
			q.pop();
			if (ok[v]) continue;
			cur++;
			ok[v] = 1;
			for (int to : E[v]) q.push(to);
		}
	}
	return cur;
}

int main() {
	scanf("%d %d %d", &n, &m, &q);
	
	E.resize(n);
	
	vector<pair<int, int>> edges;
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		edges.push_back({ a - 1, b - 1 });
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
	}
	
	bfs();
	
	//for (int i = 0; i < n; i++) err("%d, ", d[i]); err("\n");
	
	for (int i = 0; i < m; i++) {
		if (d[edges[i].first] + 1 == d[edges[i].second]) good[i] = 1;
		if (d[edges[i].second] + 1 == d[edges[i].first]) good[i] = 2;
		//err("good (%d, %d) = %d\n", edges[i].first, edges[i].second, good[i]);
	}
	
	vector<int> ask(q), ans;
	for (int i = 0; i < q; i++) {
		scanf("%d", &ask[i]);
		ask[i]--;
		used[ask[i]] = 1;
	}
	
	for (int i = 0; i < m; i++) if (!used[i])
		ask.push_back(i);
	
	reverse(ask.begin(), ask.end());
	
	init();
	
	ok[0] = 1;
	
	int cur = 1;
	for (int it = 0; it < m; it++) {
		ans.push_back(n - cur);
		
		int i = ask[it];
		if (good[i] == 1) cur += add(edges[i].first, edges[i].second);
		if (good[i] == 2) cur += add(edges[i].second, edges[i].first);
	}
	
	reverse(ans.begin(), ans.end());
	for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
	return 0;
}