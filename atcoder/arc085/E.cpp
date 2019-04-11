#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;


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


const int dd = 107;
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

int main() {
	int n;
	cin >> n;
	
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];
	
	ll sum = 0;
	int S = n + 1, T = n + 2;
	
	N = n + 3;
	E.resize(N);
	
	for (int i = 1; i <= n; i++) {
		for (int j = 2 * i; j <= n; j += i) {
			add(i, j, (ll)1e18);
		}
		if (a[i] > 0) add(i, T, a[i]), sum += a[i];
		else add(S, i, -a[i]);
	}
	cout << sum - findflow(S, T) << "\n";
	return 0;
}