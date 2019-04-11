#include <bits/stdc++.h>

using namespace std;

const int dd = 1e6 + 7;

int G[dd], P[dd];
int T[4 * dd];

void upd(int v, int tl, int tr, int pos, int val) {
	if (tl == tr)
		T[v] = val;
	else {
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			upd(v * 2, tl, tm, pos, val);
		else
			upd(v * 2 + 1, tm + 1, tr, pos, val);
		T[v] = T[v * 2] ^ T[v * 2 + 1];
	}
}

int get(int v, int tl, int tr, int l, int r) {
	if (l == tl && tr == r)
		return T[v];
	
	int tm = (tl + tr) / 2;
	if (r <= tm)
		return get(v * 2, tl, tm, l, r);
	if (l > tm)
		return get(v * 2 + 1, tm + 1, tr, l, r);
		
	return get(v * 2, tl, tm, l, tm) ^ get(v * 2 + 1, tm + 1, tr, tm + 1, r);
}

struct req {
	int l, r, ind;
};

vector<req> E[dd];

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &G[i]);
		P[i + 1] = P[i] ^ G[i];
	}
	
	int m;
	scanf("%d", &m);
	
	vector<int> ans(m);
	
	for (int i = 0; i < m; ++i) {
		req cur;
		scanf("%d %d", &cur.l, &cur.r);
		cur.ind = i;
		
		cur.l--, cur.r--;
		
		E[cur.r].push_back(cur);
	}
	
	map<int, int> M;
	
	for (int i = 0; i < n; i++) {
		if (M.count(G[i])) {
			upd(1, 0, n, M[G[i]], 0);
		}
		upd(1, 0, n, i, G[i]);
		M[G[i]] = i;
		
		for (auto c : E[i]) {
			ans[c.ind] = get(1, 0, n, c.l, c.r) ^ P[c.r + 1] ^ P[c.l];
		}
	}
	
	for (int i = 0; i < m; ++i)
		printf("%d\n", ans[i]);
		
	return 0;
}