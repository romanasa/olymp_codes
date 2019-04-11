#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int dd = (int)1e6 + 1;
const int p = 239017;

ull P[dd];
int a[dd], h[dd], G[dd];

struct SegmentTree {
	int cnt[4 * dd];
	ull h[4 * dd];
	
	void upd(int v, int tl, int tr, int pos, int c, int val) {
		if (tl == tr) {
			cnt[v] = c, h[v] = val;
		} else {
			int tm = (tl + tr) / 2;
			if (pos <= tm) upd(v * 2, tl, tm, pos, c, val);
			else upd(v * 2 + 1, tm + 1, tr, pos, c, val);
			
			h[v] = h[v * 2] * P[cnt[v * 2 + 1]] + h[v * 2 + 1];
			cnt[v] = cnt[v * 2] + cnt[v * 2 + 1];
		}
	}
} T;

int main() {
	P[0] = 1;
	for (int i = 1; i < dd; i++) P[i] = P[i - 1] * p;
	
	int n, m;
	scanf("%d %d", &n, &m);
	
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < m; i++) scanf("%d", &h[i]);
	
	copy(h, h + m, G);
	sort(G, G + m);
	for (int i = 0; i < m; i++) h[i] = lower_bound(G, G + m, h[i]) - G + 1;
	
	ull hashadd = 0, curh = 0;
	
	for (int i = 0; i < n; i++) {
		T.upd(1, 0, m, h[i], 1, i + 1);
		hashadd += P[i];
		curh = curh * p + a[i];
	}
	
	vector<int> ans;
	for (int i = 0; i + n <= m; i++) {
		if (curh == T.h[1]) ans.push_back(i + 1);
		T.upd(1, 0, m, h[i], 0, 0);
		if (i + n < m) {
			T.upd(1, 0, m, h[i + n], 1, i + n + 1);
			curh += hashadd;
		}
	}
	
	printf("%d\n", (int)ans.size());
	for (int x : ans) printf("%d ", x);	
	return 0;
}