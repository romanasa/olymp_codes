#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)3e5 + 1;
int A[dd], nxt[dd];
int sz, st[dd], ind[dd];
vector<pair<int, int> > E[dd];
vector<int> Q[dd];
ll ans[dd];

struct FenwickTree {
	ll T[dd];
	void upd(int pos, ll val) { for (int i = pos + 1; i < dd; i += (i&-i)) T[i] += val; }
	ll get(int pos) {
		ll res = 0;
		for (int i = pos + 1; i; i -= (i&-i)) res += T[i];
		return res;
	}
	ll get(int l, int r) { return get(r) - get(l - 1); }
} T1, T2, T3, T4;

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	
	for (int i = 0; i < n; i++) scanf("%d", &A[i]);
	fill(nxt, nxt + n, n);
	
	for (int i = n - 1; i >= 0; i--) {
		while (sz && st[sz - 1] <= A[i]) sz--;
		if (sz) nxt[i] = ind[sz - 1];
		st[sz] = A[i], ind[sz] = i;
		sz++;
		Q[nxt[i]].push_back(i);
	}
	
	for (int i = 0; i < q; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		l--, r--;
		ll cur = 0;
		//for (int j = l; j <= r; j++) cur += 1ll * j * min(nxt[j], r + 1);
		cur -= 1ll * r * (r + 1) * (2 * r + 1) / 6;
		cur += 1ll * l * (l - 1) * (2 * l - 1) / 6;
		//for (int j = l; j <= r; j++) cur -= 1ll * (l - 1) * min(nxt[j], r + 1);
		cur += 1ll * (l - 1) * (l + r) * (r - l + 1) / 2;
		ans[i] = cur;
		E[r].push_back({ l, i });
	}
	
	for (int i = 0; i < n; i++) {
		T3.upd(i, i);
		T4.upd(i, 1);
	}
	
	
	for (int r = 0; r < n; r++) {
		for (auto c : E[r]) {
			ans[c.second] += T1.get(c.first, r) + T3.get(c.first, r) * (r + 1);
			ans[c.second] -= 1ll * (c.first - 1) * (T2.get(c.first, r) + T4.get(c.first, r) * (r + 1));
		}
		
		for (int i : Q[r + 1]) {
			T1.upd(i, 1ll * i * nxt[i]);
			T2.upd(i, nxt[i]);
			T3.upd(i, -i);
			T4.upd(i, -1);
		}
	}
	
	for (int i = 0; i < q; i++) printf("%lld\n", ans[i]);
	return 0;
}