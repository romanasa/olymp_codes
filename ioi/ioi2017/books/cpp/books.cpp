#include "books.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e6 + 1;

int used[dd], color[dd];
int L[dd], R[dd];
int lmin, rmax;
pair<int, int> go[dd];

vector<int> cur;

void dfs(int v, vector<int> &p) {
	used[v] = 1;
	cur.push_back(v);
	if (!used[p[v]]) dfs(p[v], p);
}

struct SegmentTree {
	int mn[4 * dd], mx[4 * dd];
	void build(int v, int tl, int tr) {
		if (tl == tr) mn[v] = L[tl], mx[v] = R[tl];
		else {
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm); build(v * 2 + 1, tm + 1, tr);
			mn[v] = min(mn[v * 2], mn[v * 2 + 1]);
			mx[v] = max(mx[v * 2], mx[v * 2 + 1]);
		}
	}
	pair<int, int> get(int v, int tl, int tr, int l, int r) {
		if (tl == l && tr == r) return { mn[v], mx[v] };
		else {
			int tm = (tl + tr) / 2;
			if (r <= tm) return get(v * 2, tl, tm, l, r);
			if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r);
			auto c1 = get(v * 2, tl, tm, l, tm);
			auto c2 = get(v * 2 + 1, tm + 1, tr, tm + 1, r);
			return { min(c1.first, c2.first), max(c1.second, c2.second) }; 
		}
	}
} T;

int n;
pair<int, int> get(int l, int r) {
	//int pos1 = l, pos2 = r;
	//for (int j = l; j <= r; j++) pos1 = min(pos1, L[j]), pos2 = max(pos2, R[j]);
	return T.get(1, 0, n - 1, l, r);
}

void expand(int &l, int &r) {
	while (1) {
		auto c = get(l, r);
		int nl = c.first, nr = c.second;
		if (nl == l && nr == r) return;
		l = nl, r = nr;
	}
}

ll calc(int l, int r) {	
	expand(l, r);
	if (l == lmin && r == rmax) return 0;
	
	ll ans1 = 0;
	int l1 = l, r1 = r;
	while (r1 < rmax) {
		ans1 += 2;
		r1++;
		expand(l1, r1);
		if (l1 < l) break;
	}
	
	ll ans2 = 0;
	int l2 = l, r2 = r;
	while (l2 > lmin) {
		ans2 += 2;
		l2--;
		expand(l2, r2);
		if (r2 > r) break;
	}
	
	if (l1 == l2 && r1 == r2) return min(ans1, ans2) + calc(l1, r1);
	return ans1 + ans2;
}

ll minimum_walk(vector<int> p, int s) {
	int n = (int)p.size();
	::n = n;
	
	vector<vector<int> > t;
	
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			cur.clear();
			dfs(i, p);
			//if (cur.size() == 1) continue;
			sort(cur.begin(), cur.end());
			for (int x : cur) color[x] = (int)t.size();
			t.push_back(cur);
		}
	}
	
	lmin = s, rmax = s;
	for (int i = 0; i < (int)t.size(); i++) {
		if (t[i].size() > 1) lmin = min(lmin, t[i][0]), rmax = max(rmax, t[i].back());
	}	
	
	for (int i = 0; i < n; i++) {
		L[i] = t[color[i]][0];
		R[i] = t[color[i]].back();
	}
	T.build(1, 0, n - 1);
		
	/*
	for (int i = 0; i < n; i++) err("color[%d] = %d\n", i, color[i]);
	for (int i = 0; i < n; i++) err("L[%d] = %d\n", i, L[i]);
	for (int i = 0; i < n; i++) err("R[%d] = %d\n", i, R[i]);
	*/
	
	ll ans = 0;
	for (int i = 0; i < n; i++) ans += abs(p[i] - i);

	//err("ans = %I64d\n", ans);	
	if (t.size()) ans += calc(s, s);

	return ans;
}
