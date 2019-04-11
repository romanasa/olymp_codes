#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;
const int sz = 400;

ll ans[dd];
int a[dd];

struct SegmentTree {
	int T[4 * dd];
	int N = 1;
	
	void init(int n) {
		while (N < n) N *= 2;
	}
	
	void upd(int v, int tl, int tr, int pos, int val) {
		pos += N;
		while (pos > 0) {
			T[pos] += val;
			pos /= 2;
		}
		
		/*if (tl == tr) T[v] += val;
		else {
			int tm = (tl + tr) / 2;
			if (pos <= tm) upd(v * 2, tl, tm, pos, val);
			else upd(v * 2 + 1, tm + 1, tr, pos, val);
			T[v] = T[v * 2] + T[v * 2 + 1];
		}*/
	}
	int get(int v, int tl, int tr, int l, int r) {
		/*if (tl == l && tr == r) return T[v];
		int tm = (tl + tr) / 2;
		if (r <= tm) return get(v * 2, tl, tm, l, r);
		if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r);
		return get(v * 2, tl, tm, l, tm) + get(v * 2 + 1, tm + 1, tr, tm + 1, r);*/
		
		l += N, r += N;
		
		int s = 0;
		while (l < r) {
			if (l & 1) s += T[l], l++;
			if ((r & 1) == 0) s += T[r], r--;
			l /= 2, r /= 2;
		}
		
		if (l <= r) s += T[l];
		return s;
	}
} T;

struct ev {
	int l, r, id, ind;
	bool operator < (const ev &a) const {
		if (id == a.id) {
			if (id & 1) return r > a.r;
			return r < a.r;
		}
		return id < a.id;
	}
} Q[dd];

ll cnt;
int n;

void updR(int x, int t) {
	cnt += t * (x < n - 1 ? T.get(1, 0, n - 1, x + 1, n - 1) : 0);
	T.upd(1, 0, n - 1, x, t);
}

void updL(int x, int t) {
	cnt += t * (x > 0 ? T.get(1, 0, n - 1, 0, x - 1) : 0);
	T.upd(1, 0, n - 1, x, t);
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
	}
	
	T.init(n);
	
	int q; cin >> q;
	
	for (int i = 0; i < q; i++) {
		cin >> Q[i].l >> Q[i].r;
		Q[i].l--, Q[i].r--;
		Q[i].id = Q[i].l / sz;
		Q[i].ind = i;
	}
	
	sort(Q, Q + q);
	
	int L = 0, R = -1;
	for (int i = 0; i < q; i++) {
		while (R < Q[i].r) updR(a[++R], 1);
		while (L > Q[i].l) updL(a[--L], 1);
		while (R > Q[i].r) updR(a[R--], -1);
		while (L < Q[i].l) updL(a[L++], -1);
		ans[Q[i].ind] = cnt;
	}
	
	for (int i = 0; i < q; i++) cout << ans[i] << "\n";
	return 0;
}