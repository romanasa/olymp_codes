#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int N = (int)1e9 + 1;
const int dd = (int)1e7 + 1;

int L[dd], R[dd];
int T[dd], P[dd];

int nv = 1;

int newnode() {
	int cur = nv++;
	L[cur] = R[cur] = -1;
	T[cur] = P[cur] = 0;
	return cur;
}

void upd(int v, int tl, int tr, int l, int r) {
	if (tl == l && tr == r) {
		T[v] = tr - tl + 1;
		P[v] = 1;
	} else {
		int tm = (tl + tr) / 2;
		
		if (r <= tm) {
			if (L[v] == -1) L[v] = newnode();
			upd(L[v], tl, tm, l, r);
		} else if (l > tm) {
			if (R[v] == -1) R[v] = newnode();
			upd(R[v], tm + 1, tr, l, r);
		} else {
			if (L[v] == -1) L[v] = newnode();
			if (R[v] == -1) R[v] = newnode();
		
			upd(L[v], tl, tm, l, tm);
			upd(R[v], tm + 1, tr, tm + 1, r);
		}
		T[v] = T[L[v]] + T[R[v]];
		if (P[v]) T[v] = (tr - tl + 1);
	}
}

int get(int v, int tl, int tr, int l, int r) {
	if (v == -1) return 0;
	
	if (tl == l && tr == r) return T[v];
	if (P[v]) return (r - l + 1);

	int tm = (tl + tr) / 2;	
	
	if (r <= tm) return get(L[v], tl, tm, l, r); 
	if (l > tm) return get(R[v], tm + 1, tr, l, r);
	
	return get(L[v], tl, tm, l, tm) + get(R[v], tm + 1, tr, tm + 1, r);
}

#define TASK "f"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int root = newnode();
	int q;
	cin >> q;
		
	int c = 0;
	
	for (int i = 0; i < q; i++) {
		int t, l, r;
		cin >> t >> l >> r;
		
		l += c;
		r += c;
		
		if (t == 1) {
			cout << (c = get(root, 1, N, l, r)) << "\n";
		} else {
			upd(root, 1, N, l, r);
		}
	}
	return 0;
}