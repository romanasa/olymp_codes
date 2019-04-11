#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;


struct line {
	ll k, b;
	line() {}
	line(ll a, ll b): k(a), b(b) {}
	ll get(ll x) { return k * x + b; }
};

const int dd = (int)1e5 + 7;

struct node {
	node *L, *R;
	line cur;
} mem[dd * 20];

int nv = 0;

node* newnode() {
	int cur = nv++;
	mem[cur].L = mem[cur].R = NULL;
	mem[cur].cur.k = 0; mem[cur].cur.b = (ll)1e18;
	return &mem[cur];	
}

void upd(node *cur, int tl, int tr, line v) {
	int tm = (tl + tr) / 2;
	bool lessL = v.get(tl) < cur->cur.get(tl);
	bool lessM = v.get(tm) < cur->cur.get(tm);
	
	if (lessM) swap(cur->cur, v);
	
	if (tl == tr) return;
	
	if (lessL != lessM) {
		if (!cur->L) cur->L = newnode();
		upd(cur->L, tl, tm, v);
	} else {
		if (!cur->R) cur->R = newnode();
		upd(cur->R, tm + 1, tr, v);
	}
}

ll get(node *cur, int tl, int tr, int x) {
	ll res = cur->cur.get(x);
	if (tl == tr) return res;
	
	int tm = (tl + tr) / 2;
	
	if (x <= tm && cur->L) res = min(res, get(cur->L, tl, tm, x));
	if (x > tm && cur->R) res = min(res, get(cur->R, tm + 1, tr, x));
	return res;
}

int main() {
	int n;
	cin >> n;
	
	vector<ll> a(n), c(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> c[i];
	
	node *root = newnode();	
	
	vector<ll> dp(n);
	dp[0] = 0;
	upd(root, 0, (int)1e9, line(c[0], 0));

	for (int i = 1; i < n; i++) {
		dp[i] = get(root, 0, (int)1e9, a[i]);
		//err("dp[%d] = %I64d\n", i, dp[i]);
		upd(root, 0, (int)1e9, line(c[i], dp[i]));
	}
	cout << dp[n - 1] << "\n";
	return 0;
}