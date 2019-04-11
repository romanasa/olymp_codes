#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct req {
	int tp, l, r;
};

struct node {
	int val;
	int L, R;
	int len;
};

const int dd = (int)8e5 + 7;

int G[dd];
int iG;

node merge(node A, node B) {
	node C;
	
	C.val = max(A.val, B.val);
	C.L = A.L, C.R = B.R;
	C.len = A.len + B.len;
	C.val = max(C.val, A.R + B.L);
	
	if (A.val == A.len) C.L = A.len + B.L, C.val = max(C.val, C.L);
	if (B.val == B.len) C.R = B.len + A.R, C.val = max(C.val, C.R);
	return C;
}


struct SegmentTree {
	node T[4 * dd];
	
	void build(int v, int tl, int tr) {
		if (tl == tr) {
			int len = G[tl + 1] - G[tl];	
			T[v] = { len, len, len, len };
		} else {
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm);
			build(v * 2 + 1, tm + 1, tr);
			T[v] = merge(T[v * 2], T[v * 2 + 1]);
		}
	}
	
	void upd(int v, int tl, int tr, int pos) {
		if (tl == tr) {
			
			if (T[v].val) T[v].val = T[v].L = T[v].R = 0;
			else T[v].val = T[v].L = T[v].R = 1;
			
		} else {
			int tm = (tl + tr) / 2;
			if (pos <= tm) upd(v * 2, tl, tm, pos);
			else upd(v * 2 + 1, tm + 1, tr, pos);
			T[v] = merge(T[v * 2], T[v * 2 + 1]);
		}
	}
	
	node get(int v, int tl, int tr, int l, int r) {
		if (tl == l && tr == r) return T[v];
		int tm = (tl + tr) / 2;
		if (r <= tm) return get(v * 2, tl, tm, l, r);
		if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r);
		return merge(get(v * 2, tl, tm, l, tm), get(v * 2 + 1, tm + 1, tr, tm + 1, r));
	}
} Q;


#define TASK "crystal"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	vector<req> T(n);
	
	for (int i = 0; i < n; i++) {
		char c;
		cin >> c;
		
		if (c == 'A') {
			int x;
			cin >> x;
			T[i] = { 1, x, x };
			G[iG++] = x;
			G[iG++] = x + 1;
		} else {
			int l, r;
			cin >> l >> r;
			T[i] = { 2, l, r };
			G[iG++] = l;
			G[iG++] = r + 1;
		}
	}
	
	sort(G, G + iG);
	iG = unique(G, G + iG) - G;
	
	Q.build(1, 0, iG - 2);	
	
	for (int i = 0; i < n; i++) {
		if (T[i].tp == 1) {
			int pos = lower_bound(G, G + iG, T[i].l) - G;
			Q.upd(1, 0, iG - 2, pos);
		} else {
			int l = lower_bound(G, G + iG, T[i].l) - G;
			int r = upper_bound(G, G + iG, T[i].r) - G - 1;
			cout << Q.get(1, 0, iG - 2, l, r).val << "\n";
		}
	}
	
	return 0;
}