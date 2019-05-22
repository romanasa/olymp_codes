#include <bits/stdc++.h>
#define ll long long

using namespace std;

#define TASK "repair"

const int dd = (int)2e5 + 7;

struct SegTree {
	int T[4 * dd + 7];
	void clear() { fill(T, T + 4 * dd + 7, 0); }
	
	void upd(int v, int tl, int tr, int pos, int val) {
		if (tl == tr) {
			T[v] += val;
		} else {
			int tm = (tl + tr) / 2;
			if (pos <= tm)
				upd(v * 2, tl, tm, pos, val);
			else
				upd(v * 2 + 1, tm + 1, tr, pos, val);
				
			T[v] = T[v * 2] + T[v * 2 + 1];
		}
	}
	
	int get(int v, int tl, int tr, int l, int r) {
		if (l == tl && r == tr)
			return T[v];
		int tm = (tl + tr) / 2;
		if (r <= tm)
			return get(v * 2, tl, tm, l, r);
		if (l > tm)
			return get(v * 2 + 1, tm + 1, tr, l, r);
		return get(v * 2, tl, tm, l, tm) + get(v * 2 + 1, tm + 1, tr, tm + 1, r);
	}
} F;


struct rect { int x1, y1, x2, y2; } R[dd];
struct req { int tp, y1, y2, ind; };
vector<req> E[dd];
int ans[dd], q;

void make(set<pair<int, int> > S, int t) {
	F.clear();
	for (int i = 0; i < dd; i++)
		E[i].clear();
			
	for (auto c : S) {
		E[c.first].push_back({ 0, c.second });
	}
		
	for (int i = 0; i < q; i++) {
		if (R[i].y1 > R[i].y2 || R[i].x1 > R[i].x2)
			continue;
		E[R[i].x1].push_back({ -1, R[i].y1, R[i].y2, i });
		E[R[i].x2].push_back({ 1, R[i].y1, R[i].y2, i });
	}
		
	for (int i = 0; i < dd; i++) {
		sort(E[i].begin(), E[i].end(), [](req a, req b) { return a.tp < b.tp; });
		for (auto c : E[i]) {
			if (c.tp == -1) 
				ans[c.ind] -= t * F.get(1, 0, dd, c.y1, c.y2);
			if (c.tp == 0) 
				F.upd(1, 0, dd, c.y1, 1);
			if (c.tp == 1)
				ans[c.ind] += t * F.get(1, 0, dd, c.y1, c.y2);
		}
	}
}


int main() {
#ifndef HOME
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif

	int a, b, n;
	scanf("%d %d\n%d %d", &a, &b, &n, &q);
	
	set<pair<int, int> > A, D, L;
	
	for (int i = 0; i < n - 1; i++) {
		char c;
		int x, y;
		scanf("\n%c %d %d", &c, &x, &y);
		
		if (c == 'h') {
			A.insert({ x, y });
			A.insert({ x + 1, y });
			D.insert({ x, y });
		} else {
			A.insert({ x, y });
			A.insert({ x, y + 1 });
			L.insert({ x, y });
		}
	}
	
	for (int i = 0; i < q; i++) {
		scanf("%d %d %d %d", &R[i].x1, &R[i].y1, &R[i].x2, &R[i].y2);
	}	
	
	make(A, 1);
	
	for (int i = 0; i < q; i++)
		R[i].x2--;

	make(D, -1);

	for (int i = 0; i < q; i++)
		R[i].x2++, R[i].y2--;
	
	make(L, -1);
		
	for (int i = 0; i < q; i++)
		printf("%d\n", ans[i]);
	return 0;
}