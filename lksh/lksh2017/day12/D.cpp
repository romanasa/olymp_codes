#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;

struct edge {
	int v, to, c, ind;
	bool operator < (const edge &b) const {
		return c == b.c ? ind < b.ind : c < b.c;
	}
};

struct dsu {
	int P[dd], R[dd];
	
	dsu() { for (int i = 0; i < dd; i++) P[i] = i, R[i] = 1; }
	
	int get(int v) { return v == P[v] ? v : P[v] = get(P[v]); }
	
	inline void un(int a, int b) {
		a = get(a), b = get(b);
		if (a != b) {
			if (R[b] > R[a]) swap(a, b);
			P[b] = a, R[a] += R[b];
		}
	}
} J;

int main() {
	int n, m, d;
	scanf("%d %d %d", &n, &m, &d);
	
	vector<edge> edges;
	
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		edges.push_back({ a, b, c, i });
	}
	
	sort(edges.begin(), edges.end());
	int ans = 0, ok = 0;
	for (int i = 0; i < m; i++) {
		if (edges[i].ind < n - 1) {
			ok |= (edges[i].c < d);
			J.un(edges[i].v, edges[i].to);
		} else if (J.get(edges[i].v) != J.get(edges[i].to)) {
			ans++, J.un(edges[i].v, edges[i].to);
		}
	}
	
	printf("%d\n", ans - ok);
	return 0;
}