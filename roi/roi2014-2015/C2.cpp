#include <bits/stdc++.h>
#define ll long long
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

#define TASK "lamps"

const int dd = (int)6e5 + 7;

struct SegmentTreeSum {
	ll S[4 * dd], P[4 * dd];
	
	SegmentTreeSum() { fill(P, P + 4 * dd, -1);}
	
	void push(int v, int tl, int tr) {
		if (P[v] != -1) {
			P[v * 2] = P[v * 2 + 1] = P[v];
			S[v] = (tr - tl + 1) * P[v];
			P[v] = -1;
		}
	}
	
	int get(int v, int tl, int tr, int pos) {
		push(v, tl, tr);
		if (tl == tr)
			return S[v];
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			return get(v * 2, tl, tm, pos);
		return get(v * 2 + 1, tm + 1, tr, pos);
	}
	
	void upd(int v, int tl, int tr, int l, int r, int val) {
		push(v, tl, tr);	
		if (l == tl && r == tr) {
			P[v] = val;
			push(v, tl, tr);	
		} else {
			int tm = (tl + tr) / 2;
			if (r <= tm)
				upd(v * 2, tl, tm, l, r, val);
			else if (l > tm)
				upd(v * 2 + 1, tm + 1, tr, l, r, val);
			else
				upd(v * 2, tl, tm, l, tm, val), upd(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
	
			push(v * 2, tl, tm);
			push(v * 2 + 1, tm + 1, tr);
				
			S[v] = S[v * 2] + S[v * 2 + 1];
		}
	}
	ll get() {
		return S[1];
	}
} T;

struct SegmentTreePaint {
	int T[4 * dd], P[4 * dd];
	SegmentTreePaint() { fill(P, P + 4 * dd, -1); }
	
	void push(int v, int tl, int tr) {
		if (P[v] != -1) {
			P[v * 2] = P[v * 2 + 1] = P[v];
			T[v] = (tr - tl + 1) * (1 - P[v]);	
			P[v] = -1;
		}
	} 
	
	void upd(int v, int tl, int tr, int l, int r, int val) {
		push(v, tl, tr);	
		if (l == tl && r == tr) {
			P[v] = val;
			T[v] = (tr - tl + 1) * (1 - P[v]);
		} else {
			int tm = (tl + tr) / 2;
			if (r <= tm)
				upd(v * 2, tl, tm, l, r, val);
			else if (l > tm)
				upd(v * 2 + 1, tm + 1, tr, l, r, val);
			else
				upd(v * 2, tl, tm, l, tm, val), upd(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
			
			push(v * 2, tl, tm);
			push(v * 2 + 1, tm + 1, tr);
				
			T[v] = T[v * 2] + T[v * 2 + 1];
		}
	}
	
	int get(int v, int tl, int tr, int l, int r) {
		push(v, tl, tr);
		if (l == tl && r == tr) 
			return T[v];
		int tm = (tl + tr) / 2;
		if (r <= tm)
			return get(v * 2, tl, tm, l, r);
		if (l > tm)
			return get(v * 2 + 1, tm + 1, tr, l, r);
		return get(v * 2, tl, tm, l, tm) + get(v * 2 + 1, tm + 1, tr, tm + 1, r);
	}
	
	int get(int v, int tl, int tr, int k) {
		push(v, tl, tr);
		if (tl == tr)
			return tl;	
		int tm = (tl + tr) / 2;
		push(v * 2, tl, tm);
		if (T[v * 2] >= k) {
			return get(v * 2, tl, tm, k);
		}
		return get(v * 2 + 1, tm + 1, tr, k - T[v * 2]);
	}
} J;

char S[dd];

int main() {
#ifndef HOME
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif

	int n, q;
	scanf("%d %d", &n, &q);
	scanf("%s", S);	
	
	int ind = n;
	for (int i = n - 1; i >= 0; i--) {
		if (S[i] == '0') {
			ind = i;
		}
		J.upd(1, 0, n, i, i, S[i] - '0');
		T.upd(1, 0, n, i, i, ind);
	}
	ll t = 1ll * n * (n - 1) / 2;
	printf("%lld\n", T.get() - t);
	
	while (q--) {
		int l, r, c;
		scanf("%d %d %d", &l, &r, &c);
		l--, r--;	
		
		if (c == 0) {
			J.upd(1, 0, n, l, r, 0);
		} else {
			J.upd(1, 0, n, l, r, 1);
			
			int t = J.get(1, 0, n, 0, l);
			l = J.get(1, 0, n, t) + (t > 0);			
			
			t = J.get(1, 0, n, 0, r);
			r = J.get(1, 0, n, t + 1) - 1;
				
			int il = l, ir = r + 1;
			
			while (ir - il > 1) {
				int m = (il + ir) / 2;
				
				if (T.get(1, 0, n, m) < r + 1)
					il = m;
				else
					ir = m;
			}
			
			if (T.get(1, 0, n, il) < r + 1)
				T.upd(1, 0, n, l, il, r + 1);
		}		
		printf("%lld\n", T.get() - t);
	}
	
	return 0;
}