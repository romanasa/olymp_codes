#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct node {
	int bal, mbal;
};

node merge(node A, node B) {
	node C;
	C.bal = A.bal + B.bal;
	C.mbal = min(A.mbal, A.bal + B.mbal);
	return C;
}

const int dd = (int)1e5 + 1;
node T[4 * dd];

void build(int v, int tl, int tr, string &s) {
	if (tl == tr) {
		int cur = s[tl] == '(' ? 1 : -1; 
		T[v] = { cur, cur };
	} else {
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, s);
		build(v * 2 + 1, tm + 1, tr, s);
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

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	string s;
	cin >> s;
	
	int n = (int)s.size();
	build(1, 0, n - 1, s);
	
	int q;
	cin >> q;
	
	while (q--) {
		int l, r;
		cin >> l >> r;
		
		node cur = get(1, 0, n - 1, l - 1, r - 1);
		
		err("cur = (%d, %d)\n", cur.bal, cur.mbal);
		
		if (cur.bal == 0 && cur.mbal >= 0) puts("YES");
		else puts("NO");
	}
	
	return 0;
}