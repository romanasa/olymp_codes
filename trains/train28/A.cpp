#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct node {
	ll A, B, C;
	ll get(ll x) {
		if (x <= A) return C;
		if (x >= B) return C + (B - A);
		return C + (x - A);
	}
};

node merge(node L, node R) {
	node C;

	ll outL1 = L.C;
	ll outL2 = L.C + (L.B - L.A);
	
	if (outL2 <= R.A) {
		C.A = C.B = R.A;
		C.C = R.C;
		return C;
	}
	
	if (outL1 >= R.B) {
		C.A = C.B = R.B;
		C.C = R.C + (R.B - R.A);
		return C;
	}
	ll Q = max(outL1, R.A);
	ll W = min(outL2, R.B);
	
	assert(Q <= W);
	
	C.A = Q, C.B = W;
	C.C = R.get(Q);
	return C;
}

const int dd = (int)1e5 + 7;
int n, vmax, v2;

struct SegmentTree {
	node T[4 * dd];
	
	SegmentTree() { for (int i = 0; i < 4 * dd; i++) T[i].A = 0, T[i].B = (ll)1e9, T[i].C = 0; }
	
	void upd(int v, int tl, int tr, int pos, node val) {
		if (tl == tr) T[v] = val;
		else {
			int tm = (tl + tr) / 2;
			if (pos <= tm) upd(v * 2, tl, tm, pos, val);
			else upd(v * 2 + 1, tm + 1, tr, pos, val);
			T[v] = merge(T[v * 2], T[v * 2 + 1]);
		}
	}
	
	bool check(int x) {
		return T[1].C <= x && x <= T[1].C + (T[1].B - T[1].A);
	}
	
	int get(int x) {
		if (T[1].C == x) return T[1].A;
		if (T[1].C + (T[1].B - T[1].A) == x) return vmax;
		return x - T[1].C;
	}
} T;


int main() {
	cin >> n >> vmax >> v2;
	
	vector<char> op(n);
	vector<int> t(n);
	
	int pr = -(int)2e9 - 5;
	vector<pair<int, int> > Q;
	
	for (int i = 0; i < n; i++) {
		cin >> op[i];
		cin >> t[i];
		
		Q.push_back({ t[i] - pr, i });
		pr = t[i];
	}
	
	for (int i = 0; i < n; i++) {
		if (op[i] == '-') T.upd(1, 0, n - 1, i, { 1, vmax, 0 });
		else T.upd(1, 0, n - 1, i, { 0, vmax - 1, 1 });
	}
	
	if (T.check(v2)) return 0 * puts("infinity");
	
	sort(Q.rbegin(), Q.rend());
	
	int i = 0;
	while (i < (int)Q.size()) {
		int cur = Q[i].first;
		
		while (i < (int)Q.size() && cur == Q[i].first) {
			T.upd(1, 0, n - 1, Q[i].second, { 0, vmax, 0 });
			i++;
		}
		
		if (T.check(v2)) {
			cout << cur - 1 << " " << T.get(v2) << "\n";
			return 0;
		}
	}
	return 0;
}