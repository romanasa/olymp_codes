#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

const int dd = (int)6e5 + 7;
struct pt { int x, y, cost; } A[dd], B[dd];
int Gx[dd], Gy[dd];
int ix, iy;

struct ev { int tp, cost, a, b; };

vector<int> QA[dd];
vector<pair<int, int> > QB[dd];

vector<ev> EA[dd], EB[dd];

struct SegmentTree {
	int T[4 * dd];
	int P[4 * dd];
	void upd(int v, int tl, int tr, int l, int r, int val) {
		if (tl == l && tr == r) {
			T[v] += val;
			P[v] += val;
		} else {
			int tm = (tl + tr) / 2;
			if (r <= tm) upd(v * 2, tl, tm, l, r, val);
			else if (l > tm) upd(v * 2 + 1, tm + 1, tr, l, r, val);
			else upd(v * 2, tl, tm, l, tm, val), upd(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
			T[v] = max(T[v * 2], T[v * 2 + 1]);
			T[v] += P[v];
		}
	}
	int get() {
		return T[1];
	}
} T;

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	//for (int i = 0; i <= n; i++) Gx[ix++] = i;
	//for (int i = 0; i <= m; i++) Gy[iy++] = i;
	
	int R, E;
	scanf("%d %d", &R, &E);
	
	Gx[ix++] = 0, Gx[ix++] = n + 1;
	Gy[iy++] = 0, Gy[iy++] = m + 1;
	Gx[ix++] = 1, Gy[iy++] = 1;
	
	for (int i = 0; i < R; i++) {
		scanf("%d %d", &A[i].x, &A[i].y);
		Gx[ix++] = A[i].x; Gx[ix++] = A[i].x + 1; Gx[ix++] = A[i].x - 1;
		Gy[iy++] = A[i].y; Gy[iy++] = A[i].y + 1; Gy[iy++] = A[i].y - 1;
	}
	
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &B[i].x, &B[i].y, &B[i].cost);
		Gx[ix++] = B[i].x; Gx[ix++] = B[i].x + 1; Gx[ix++] = B[i].x - 1;
		Gy[iy++] = B[i].y; Gy[iy++] = B[i].y + 1; Gy[iy++] = B[i].y - 1;
	}
	
	sort(Gx, Gx + ix), sort(Gy, Gy + iy);
	
	
	ix = unique(Gx, Gx + ix) - Gx;
	iy = unique(Gy, Gy + iy) - Gy;
	
	for (int i = 0; i < R; i++) {
		A[i].x = lower_bound(Gx, Gx + ix, A[i].x) - Gx;
		A[i].y = lower_bound(Gy, Gy + iy, A[i].y) - Gy;
		QA[A[i].x].push_back(A[i].y);
		//err("(%d, %d), ", A[i].x, A[i].y);
	}
	//err("\n");
	
	for (int i = 0; i < E; i++) {
		B[i].x = lower_bound(Gx, Gx + ix, B[i].x) - Gx;
		B[i].y = lower_bound(Gy, Gy + iy, B[i].y) - Gy;
		QB[B[i].x].push_back({ B[i].y, B[i].cost});
		//err("(%d, %d, %d), ", B[i].x, B[i].y, B[i].cost);
	}
	//err("\n");
	
	for (int i = 1; i < ix; i++) {
		QA[i].push_back(iy - 1);
		
		sort(QA[i].begin(), QA[i].end());
		sort(QB[i].begin(), QB[i].end());
		
		int pr = 0, j = 0;
		for (int t : QA[i]) {
			while (j < (int)QB[i].size() && QB[i][j].first <= pr) j++;
			int sum = 0;
			while (j < (int)QB[i].size() && QB[i][j].first < t) sum += QB[i][j].second, j++;
			
			if (pr + 1 <= t - 1) {
				//err("i = %d, l = %d, r = %d, cost = %d\n", i, pr + 1, t - 1, sum);
				EB[pr + 1].push_back({ 0, sum, i });
				EB[t - 1].push_back({ 1, sum, i });
			}
			pr = t;
		}
	}
	
	for (int i = 1; i < dd; i++) QA[i].clear(), QB[i].clear();
	
	for (int i = 0; i < R; i++) {
		QA[A[i].y].push_back(A[i].x);
	}
	for (int i = 0; i < E; i++) {
		QB[B[i].y].push_back({ B[i].x, B[i].cost });
	}
	
	for (int i = 1; i < iy; i++) {
		QA[i].push_back(ix - 1);
		
		sort(QA[i].begin(), QA[i].end());
		sort(QB[i].begin(), QB[i].end());
		
		int pr = 0, j = 0;
		for (int t : QA[i]) {
			while (j < (int)QB[i].size() && QB[i][j].first <= pr) j++;
			int sum = 0;
			while (j < (int)QB[i].size() && QB[i][j].first < t) sum += QB[i][j].second, j++;
			
			if (pr + 1 <= t - 1) {
				//err("i = %d, l = %d, r = %d, cost = %d\n", i, pr + 1, t - 1, sum);
				EA[i].push_back({ 0, sum, pr + 1, t - 1 });
			}
			pr = t;
		}
	}
	
	int ans = 0;
	for (int i = 1; i < dd; i++) {
		for (auto c : EB[i]) if (c.tp == 0)
			T.upd(1, 1, ix - 1, c.a, c.a, c.cost);
		for (auto c : EA[i]) T.upd(1, 1, ix - 1, c.a, c.b, c.cost);
		for (auto c : QB[i]) T.upd(1, 1, ix - 1, c.first, c.first, -(int)1e9);
		
		ans = max(ans, T.get());
		
		for (auto c : QB[i]) T.upd(1, 1, ix - 1, c.first, c.first, (int)1e9);
		for (auto c : EA[i]) T.upd(1, 1, ix - 1, c.a, c.b, -c.cost);
		for (auto c : EB[i]) if (c.tp == 1)
			T.upd(1, 1, ix - 1, c.a, c.a, -c.cost);
	}
	printf("%d\n", ans);
	return 0;
}