#include <bits/stdc++.h>
#define ll long long

using namespace std;

struct edge { int a, b, c; };

const int dd = 201;

struct dsu {
	int P[dd], R[dd];
	void clear() { for (int i = 0; i < dd; i++) P[i] = i, R[i] = 1; }
	int get(int v) { return v == P[v] ? v : P[v] = get(P[v]); }
	
	bool un(int a, int b) {
		a = get(a), b = get(b); 
		if (a != b) {
			if (R[b] > R[a]) swap(a, b);
			R[a] += R[b], P[b] = a;
		}
		return a != b;
	}
} J;


int n, m;

int get(vector<edge> E) {
	sort(E.begin(), E.end(), [](edge a, edge b) { return a.c < b.c; });
	int cur = 0, comp = n;
	
	J.clear();
	for (auto c : E) {
		if (J.un(c.a, c.b))
			cur += c.c, comp--;
	}
	return comp == 1 ? cur : -1;
}

int main() {
	scanf("%d %d", &n, &m);
	
	vector<edge> E;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		E.push_back({ a - 1, b - 1, c });
		printf("%d\n", get(E));
		fflush(stdout);
	}
	return 0;
}