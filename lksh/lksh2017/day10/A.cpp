#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e6 + 1;
vector<vector<int> > E, ER;
vector<int> cur;

int used[dd], comp[dd];
int in[dd];

void topsort(int v) {
	used[v] = 1;
	for (int to : E[v]) if (!used[to]) topsort(to);
	cur.push_back(v);
}

void mark(int v, int c) {
	comp[v] = c;
	for (int to : ER[v]) if (comp[to] == -1) mark(to, c);
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	E.resize(n);
	ER.resize(n);
	
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		E[a - 1].push_back(b - 1);
		ER[b - 1].push_back(a - 1);
	}
	
	fill(used, used + n, 0);
	fill(comp, comp + n, -1);
	
	for (int i = 0; i < n; i++) if (!used[i]) topsort(i);
	
	reverse(cur.begin(), cur.end());
	
	int c = 0;
	for (int i : cur) if (comp[i] == -1) mark(i, c++);
	
	for (int v = 0; v < n; v++) {
		for (int to : E[v]) {
			if (comp[v] != comp[to]) in[comp[to]]++;
		}
	}
	
	int cnt = 0, pos = -1;
	for (int i = 0; i < c; i++) {
		if (in[i] == 0) {
			cnt++, pos = i;
		}
	}
	
	if (cnt == 1) {
		vector<int> Q;
		for (int v = 0; v < n; v++) if (comp[v] == pos) Q.push_back(v);
		printf("%d\n", (int)Q.size());
		for (int x : Q) printf("%d ", x + 1);
	} else {
		puts("0");
	}
		
	return 0;
}