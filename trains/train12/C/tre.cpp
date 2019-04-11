#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)4e5 + 1;
const int LOG = 19;

int up[LOG][dd], h[dd];
int nv = 1, root;


int create(int par) {
	int cur = nv++;
	h[cur] = (par == -1 ? 0 : h[par] + 1);
	
	up[0][cur] = (par == -1 ? cur : par);
	for (int i = 1; i < LOG; i++) up[i][cur] = up[i - 1][up[i - 1][cur]];
	return cur;
}

void init() {
	root = create(-1);
}

void path(int a, int s) {
	for (int it = 0; it < s; it++) {
		int v = create(a);
		a = v;
	}
}

int go(int v, int x) {
	for (int i = LOG - 1; i >= 0; i--) {
		if ((1 << i) <= x) {
			v = up[i][v];
			x -= (1 << i);
		}
	}
	return v;
}

int dig(int a, int b) {
	int oa = a, ob = b;
	
	for (int i = LOG - 1; i >= 0; i--) if (h[up[i][a]] >= h[b]) a = up[i][a];
	if (a == b) return go(oa, (h[oa] - h[ob]) / 2);
	
	for (int i = LOG - 1; i >= 0; i--) if (h[up[i][b]] >= h[a]) b = up[i][b];
	if (a == b) return go(ob, (h[ob] - h[oa] + 1) / 2);

	for (int i = LOG - 1; i >= 0; i--) {
		if (up[i][a] != up[i][b]) a = up[i][a], b = up[i][b];
	}
	
	int lca = up[0][a];
	int len = (h[oa] + h[ob] - 2 * h[lca]) / 2;
	
	if (len <= h[oa] - h[lca]) return go(oa, len);
	len -= (h[oa] - h[lca]);
	return go(ob, h[ob] - h[lca] - len);
}
