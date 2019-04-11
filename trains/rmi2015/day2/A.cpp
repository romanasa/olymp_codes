#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;
ll A[dd], B[dd], C[dd];

struct SegmentTreeGCD {
	ll T[4 * dd];
	void upd(int v, int tl, int tr, int pos, ll val) {
		if (tl == tr) T[v] += val;
		else {
			int tm = (tl + tr) / 2;
			if (pos <= tm) upd(v * 2, tl, tm, pos, val);
			else upd(v * 2 + 1, tm + 1, tr, pos, val);
			T[v] = __gcd(T[v * 2], T[v * 2 + 1]);
		}
	}
	ll get(int v, int tl, int tr, int l, int r) {
		if (tl == l && tr == r) return T[v];
		int tm = (tl + tr) / 2;
		if (r <= tm) return get(v * 2, tl, tm, l, r);
		if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r);
		return __gcd(get(v * 2, tl, tm, l, tm), get(v * 2 + 1, tm + 1, tr, tm + 1, r));
	}
} TC;

struct SegmentTreeSUM {
	ll A[dd], B[dd];
	
	void updA(int pos, ll val) { for (int i = pos + 1; i < dd; i += (i&-i)) A[i] += val; }
	void updB(int pos, ll val) { for (int i = pos + 1; i < dd; i += (i&-i)) B[i] += val; }
	
	void upd(int l, int r, ll val) {
		updA(l, val), updA(r + 1, -val);
		updB(l, -val * (l - 1)), updB(r + 1, val * r);
	}
	
	ll getA(int pos) {
		ll res = 0;
		for (int i = pos + 1; i; i -= (i&-i)) res += A[i];
		return res;
	}
	
	ll getB(int pos) {
		ll res = 0;
		for (int i = pos + 1; i; i -= (i&-i)) res += B[i];
		return res;
	}
	
	ll get(int pos) { return getA(pos) * pos + getB(pos); }
} TB;

#define TASK "euclid"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, k;
	scanf("%d %d", &n, &k);
	
	for (int i = 0; i < n; i++) scanf("%lld", &A[i]);
	for (int i = 0; i < n; i++) B[i] = A[i] - (i ? A[i - 1] : 0);
	for (int i = 0; i < n; i++) C[i] = B[i] - (i ? B[i - 1] : 0);
	
	for (int i = 0; i < n; i++) TB.upd(i, i, B[i]);
	for (int i = 0; i < n; i++) TC.upd(1, 0, n - 1, i, C[i]);
	
	while (k--) {
		int tp, l, r;
		scanf("%d %d %d", &tp, &l, &r);
		l--, r--;
		
		if (tp == 0) {
			ll cur1 = TB.get(l);
			ll cur2 = (l < r ? TB.get(l + 1) : 0);
			ll cur3 = (l + 1 < r ? TC.get(1, 0, n - 1, l + 2, r) : 0);
			printf("%lld\n", __gcd(cur1, __gcd(cur2, abs(cur3))));
		} else {
			int x;
			scanf("%d", &x);
			
			TB.upd(l, r, x);
			if (r + 1 < n) TB.upd(r + 1, r + 1, -1ll * x * (r - l + 1));
			
			TC.upd(1, 0, n - 1, l, x);
			if (r + 1 < n) TC.upd(1, 0, n - 1, r + 1, -1ll * x * (r - l + 2));
			if (r + 2 < n) TC.upd(1, 0, n - 1, r + 2, 1ll * x * (r - l + 1));
		}
	}
	
	return 0;
}