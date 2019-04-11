#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e6 + 7;

struct Fen {
	pair<int, int> T[4 * dd];
	int P[4 * dd];
	
	void build(int v, int tl, int tr) {
		if (tl == tr) T[v] = { 0, tl };
		else {
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm);
			build(v * 2 + 1, tm + 1, tr);
			T[v] = max(T[v * 2], T[v * 2 + 1]);
		}
	}
	
	void upd(int v, int tl, int tr, int l, int r, int val) {
		if (tl == l && tr == r) T[v].first += val, P[v] += val;
		else {
			int tm = (tl + tr) / 2;
			if (r <= tm) upd(v * 2, tl, tm, l, r, val);
			else if (l > tm) upd(v * 2 + 1, tm + 1, tr, l, r, val);
			else upd(v * 2, tl, tm, l, tm, val), upd(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
			
			T[v] = max(T[v * 2], T[v * 2 + 1]);
			T[v].first += P[v];
		}
	}
} F;

struct ev {	int tp, l, r; };

vector<ev> E[dd];

#define TASK "windows"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		
		x1 += dd / 2, x2 += dd / 2, y1 += dd / 2, y2 += dd / 2;
		
		E[x1].push_back({ 1, y1, y2 });
		E[x2].push_back({ -1, y1, y2 });
	}
	
	F.build(1, 0, dd);
	
	int ans = -1, xx = -1, yy = -1;
	
	for (int i = 0; i < dd; i++) {
		for (auto c : E[i]) if (c.tp == 1) {
			F.upd(1, 0, dd, c.l, c.r, 1);
		}
		
		auto t = F.T[1];
		
		if (t.first > ans) {
			ans = t.first;
			xx = i, yy = t.second;
		}
		
		for (auto c : E[i]) if (c.tp == -1) {
			F.upd(1, 0, dd, c.l, c.r, -1);
		}
	}
	
	printf("%d\n%d %d\n", ans, xx - dd / 2, yy - dd / 2);
	
	return 0;
}