#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)5e5 + 1;
int A[dd];

struct SegmentTree {
	ll T[4 * dd], P[4 * dd];
	
	void upd(int v, int tl, int tr, int l, int r, int val) {
		if (tl == l && tr == r) P[v] += val, T[v] += val;
		else {
			int tm = (tl + tr) / 2;
			if (r <= tm) upd(v * 2, tl, tm, l, r, val);
			else if (l > tm) upd(v * 2 + 1, tm + 1, tr, l, r, val);
			else upd(v * 2, tl, tm, l, tm, val), upd(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
			T[v] = max(T[v * 2], T[v * 2 + 1]);
			T[v] += P[v];
		}
	}
	
	ll get(int v, int tl, int tr, int l, int r) {
		if (tl == l && tr == r) return T[v];
		else {
			int tm = (tl + tr) / 2;
			if (r <= tm) return get(v * 2, tl, tm, l, r) + P[v];
			if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r) + P[v];
			return max(get(v * 2, tl, tm, l, tm), get(v * 2 + 1, tm + 1, tr, tm + 1, r)) + P[v];
		}
	}
} T2, T3;

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}
	
	for (int i = 0; i + 2 <= n; i++) {
		T2.upd(1, 0, n, i, i, A[i] + A[i + 1]);
	}
	
	for (int i = 0; i + 3 <= n; i++) {
		T3.upd(1, 0, n, i, i, A[i] + A[i + 1] + A[i + 2]);
	}
	
	while (q--) {
		int tp, l, r;
		scanf("%d %d %d", &tp, &l, &r);
		l--, r--;
		
		if (tp == 1) {
			int x;
			scanf("%d", &x);
			
			if (l == r) {
				if (l > 0) T2.upd(1, 0, n, l - 1, l - 1, x);
				T2.upd(1, 0, n, l, l, x);
				
				if (l > 1) T3.upd(1, 0, n, l - 2, l - 2, x);
				if (l > 0) T3.upd(1, 0, n, l - 1, l - 1, x);
				T3.upd(1, 0, n, l, l, x);	
			}
			
			if (l + 1 == r) {
				if (l > 1) T3.upd(1, 0, n, l - 2, l - 2, x);
				if (l > 0) T3.upd(1, 0, n, l - 1, l - 1, 2 * x);
				T3.upd(1, 0, n, l, l, 2 * x);
				T3.upd(1, 0, n, r, r, x);
			}
			
			if (l < r) {
    			if (l > 0) T2.upd(1, 0, n, l - 1, l - 1, x);
    			T2.upd(1, 0, n, l, r - 1, 2 * x);
    			T2.upd(1, 0, n, r, r, x);
			}
			
			if (l + 1 < r) {
    			if (l > 1) T3.upd(1, 0, n, l - 2, l - 2, x);//, err("(%d, %d) += %d\n", l - 2, l - 2, x);	
    			if (l > 0) T3.upd(1, 0, n, l - 1, l - 1, 2 * x);//, err("(%d, %d) += %d\n", l - 1, l - 1, 2 * x);
    			T3.upd(1, 0, n, l, r - 2, 3 * x);// err("(%d, %d) += %d\n", l, r - 2, 3 * x);
    			T3.upd(1, 0, n, r - 1, r - 1, 2 * x);// err("(%d, %d) += %d\n", r - 1, r - 1, 2 * x);	
    			T3.upd(1, 0, n, r, r, x);//err("(%d, %d) += %d\n", r, r, x);
			}			
		} else {
			
			ll t1 = T2.get(1, 0, n, l, min(r - 1, n - 2));
			ll t2 = (l + 1 < r ? T3.get(1, 0, n, l, min(r - 2, n - 3)) : 0);
			
			printf("%.4f\n", max(t1 / 2.0, t2 / 3.0));
		}
		//for (int i=  0; i < n; i++) err(" %I64d,", T3.get(1, 0, n, i, i)); err("\n");
	}
	return 0;
}