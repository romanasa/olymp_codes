#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;

int n;

struct SegmentTreeMax {
	int T[4 * dd];
	void upd(int v, int tl, int tr, int pos, int val) {
		if (tl == tr) T[v] = val;
		else {
			int tm = (tl + tr) / 2;
			if (pos <= tm) upd(v * 2, tl, tm, pos, val);
			else upd(v * 2 + 1, tm + 1, tr, pos, val);
			T[v] = max(T[v * 2], T[v * 2 + 1]);
		}
	}
	int get(int v, int tl, int tr, int l, int r) {
		if (l > r) return -1;
		if (tl == l && tr == r) return T[v];
		int tm = (tl + tr) / 2;
		return max(get(v * 2, tl, tm, l, min(tm, r)), get(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r));
	}
} A, B;

set<int> ones;
set<int> E[dd];

int P[dd];
int a[dd];


void del(int pos, int val) {
	auto it = E[val].lower_bound(pos);
	
	//err("tut\n");
	if (it != --E[val].end()) {
		auto nxt = it;
		++nxt;
		
		int nval = -1;
		if (it != E[val].begin()) nval = *prev(it);
		
		P[*nxt] = nval;
		A.upd(1, 0, n - 1, *nxt, nval);
	} 
	
	
	
	P[pos] = -1;
	A.upd(1, 0, n - 1, pos, -1);
	E[val].erase(it);
}

void add(int pos, int val) {
	if (E[val].empty()) {
		P[pos] = -1, A.upd(1, 0, n - 1, pos, -1);
		return;
	}

	auto nxt = E[val].lower_bound(pos);
	
	if (nxt == E[val].begin()) {
		P[*nxt] = pos, P[pos] = -1;
		A.upd(1, 0, n - 1, *nxt, pos);
		A.upd(1, 0, n - 1, pos, -1);
		return; 
	}
	
	auto prv = nxt;
	--prv;
	
	P[pos] = *prv;
	A.upd(1, 0, n - 1, pos, *prv);
	
	if (nxt != E[val].end()) {
		P[*nxt] = pos;
		A.upd(1, 0, n - 1, *nxt, pos);
	}
}


void upd(int pos, int val) {
	if (a[pos] == 1) ones.erase(pos);
	del(pos, a[pos]);
	
	a[pos] = val;
	B.upd(1, 0, n - 1, pos, val);
	
	add(pos, a[pos]);
	E[val].insert(pos);
	if (a[pos] == 1) ones.insert(pos);
}

#define TASK "permutation"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for (int i = 0; i < n; i++) cin >> a[i];
	
	map<int, int> pr;
	for (int i = 0; i < n; i++) {
		if (!pr.count(a[i])) P[i] = -1;
		else P[i] = pr[a[i]];
		pr[a[i]] = i;
		if (a[i] == 1) ones.insert(i);
		
		A.upd(1, 0, n - 1, i, P[i]);
		B.upd(1, 0, n - 1, i, a[i]);
		E[a[i]].insert(i);
	}
	
	int q;
	cin >> q;
	
	while (q--) {
		int t, l, r;
		cin >> t >> l >> r;
		
		if (t == 1) upd(l - 1, r);
		else {
			l--, r--;
			
			int ok = 1;
			
			auto it = ones.lower_bound(l);
			if (it == ones.end() || *it > r) ok = 0;
			
			
			if (ok && B.get(1, 0, n - 1, l, r) != (r - l + 1)) ok = 0;
			if (ok && A.get(1, 0, n - 1, l, r) >= l) ok = 0;
			cout << (ok ? "YES\n" : "NO\n");
		}
		
		//for (int i = 0; i < n; i++) err("%d, ", a[i]); err("\n");
		//for (int i = 0; i < n; i++) err("%d, ", P[i]); err("\n"); err("\n");
	}
	
	return 0;
}