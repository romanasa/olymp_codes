#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int mod = (int)1e9 + 7;

struct matr {
	ll a, b, c, d;
	
	void norm() { a %= mod, b %= mod, c %= mod, d %= mod; }
	
	matr() {a = b = c = d = 0;}
	matr(ll a, ll b, ll c, ll d) : a(a), b(b), c(c), d(d) { norm(); }
	
	matr operator * (matr m) {
		return matr(a * m.a + b * m.c, a * m.b + b * m.d, c * m.a + d * m.c, c * m.b + d * m.d);
	}
	
	matr operator + (matr m) {
		return matr(a + m.a, b + m.b, c + m.c, d + m.d);
	}
};

matr bp(matr x, ll d) {
	matr cur(1, 0, 0, 1);
	for ( ; d; d /= 2) {
		if (d & 1) cur = cur * x;
		x = x * x;
	}
	return cur;
}

const int dd = (int)2e5 + 7;

matr M[4 * dd], P[4 * dd];

void upd(int v, int tl, int tr, int l, int r, matr val) {
	if (l == tl && r == tr) {
		M[v] = M[v] * val;
		P[v] = P[v] * val;
	} else {
		int tm = (tl + tr) / 2;
		
		if (r <= tm)
			upd(v * 2, tl, tm, l, r, val);
		else if (l > tm)
			upd(v * 2 + 1, tm + 1, tr, l, r, val);
		else
			upd(v * 2, tl, tm, l, tm, val), upd(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
		
		M[v] = (M[v * 2] + M[v * 2 + 1]) * P[v];	
	}
}

matr get(int v, int tl, int tr, int l, int r) {
	if (l == tl && r == tr)
		return M[v];
	int tm = (tl + tr) / 2;
	if (r <= tm)
		return get(v * 2, tl, tm, l, r) * P[v];
	if (l > tm)
		return get(v * 2 + 1, tm + 1, tr, l, r) * P[v];
	return (get(v * 2, tl, tm, l, tm) + get(v * 2 + 1, tm + 1, tr, tm + 1, r)) * P[v];
}

int G[dd];

void build(int v, int tl, int tr) {
	P[v] = matr(1, 0, 0, 1);
	
	if (tl == tr) {
		M[v] = bp(matr(1, 1, 1, 0), G[tl]);
	} else {
		int tm = (tl + tr) / 2;
		
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm + 1, tr);
		
		M[v] = M[v * 2] + M[v * 2 + 1];
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &G[i]);
	}
	
	build(1, 0, n - 1);
	
	for (int i = 0; i < m; i++) {
		int tp, l, r, x;
		scanf("%d %d %d", &tp, &l, &r);
		if (tp == 1) {
			scanf("%d", &x);
			upd(1, 0, n - 1, l - 1, r - 1, bp(matr(1, 1, 1, 0), x));
		} else {
			printf("%d\n", get(1, 0, n - 1, l - 1, r - 1).b);
		}
	}
	return 0;
}