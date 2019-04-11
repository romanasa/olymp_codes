#include "grader.h"
#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const ll dd = (ll)5e5 + 7;

ll G[dd], A[dd];
ll iG;

struct SegmentTree {
	ll T[4 * dd];
	ll S[4 * dd];
	void clear() { fill(T, T + 4 * dd, 0); fill(S, S + 4 * dd, 0); }
	void upd(ll v, ll tl, ll tr, ll pos, ll val, ll cost) {
		if (tl == tr) {
			T[v] += val;
			S[v] += cost;
		} else {
			ll tm = (tl + tr) / 2;
			if (pos <= tm) upd(v * 2, tl, tm, pos, val, cost);
			else upd(v * 2 + 1, tm + 1, tr, pos, val, cost);
			S[v] = S[v * 2] + S[v * 2 + 1];
			T[v] = T[v * 2] + T[v * 2 + 1];
		}
	}
	ll get(ll v, ll tl, ll tr, ll k) {
		if (k <= 0) return 0;
		if (tl == tr) return min(1ll * k, T[v]) * G[tl];
		ll tm = (tl + tr) / 2;
		if (T[v * 2 + 1] >= k) return get(v * 2 + 1, tm + 1, tr, k);
		return S[v * 2 + 1] + get(v * 2, tl, tm, k - T[v * 2 + 1]);
	}
} T;

ll st;
pair<ll, ll> goL[dd], goR[dd];
ll ind[dd];

void dfs(ll l, ll r, ll oL, ll oR, pair<ll, ll> *go) {
	ll m = (l + r) / 2;
	ll opt = -1;
	ll cur = 0;
	
	for (ll j = oL; j <= oR; j++) T.upd(1, 0, iG, ind[j], -1, -A[j]);
	for (ll j = oL; j <= oR; j++) {
		T.upd(1, 0, iG, ind[j], 1, A[j]);			
		if (m - abs(st - j) > 0) {
			ll tmp = T.get(1, 0, iG, m - abs(st - j));	
			if (opt == -1 || tmp > cur) {
				cur = tmp, opt = j;
			}
		}
	}
	
	go[m] = { opt, cur };
	
	if (l <= m - 1) {
		for (ll i = opt + 1; i <= oR; i++) T.upd(1, 0, iG, ind[i], -1, -A[i]);
		dfs(l, m - 1, oL, opt, go);
		for (ll i = opt + 1; i <= oR; i++) T.upd(1, 0, iG, ind[i], 1, A[i]);
	}
	
	if (m + 1 <= r) {
		dfs(m + 1, r, opt, oR, go);
	}
}

ll calc1(int n, int start, int d, int attraction[]) {
	copy(attraction, attraction + n, A);
	copy(A, A + n, G);
	sort(G, G + n);
	iG = unique(G, G + n) - G;
	for (ll i = 0; i < n; i++) ind[i] = lower_bound(G, G + iG, A[i]) - G;
	
	ll ans = 0;
	
	T.clear();
	for (ll i = start; i < n; i++) T.upd(1, 0, iG, ind[i], 1, A[i]);
	st = start;
	dfs(0, d, start, n - 1, goR);
	T.clear();
	for (ll i = 0; i <= d; i++) ans = max(ans, goR[i].second);
	
	reverse(A, A + n);
	reverse(ind, ind + n);
	
	st = n - st - 1;
	
	for (ll i = st; i < n; i++) T.upd(1, 0, iG, ind[i], 1, A[i]);	
	dfs(0, d, st, n - 1, goL);
	for (ll i = 0; i <= d; i++) ans = max(ans, goL[i].second);
	return ans;	
}

ll calc2(int n, int start, int d, int attraction[]) {
	for (int i = 0; i < n; i++) A[2 * i] = 0, A[2 * i + 1] = attraction[i];
	copy(A, A + 2 * n, G);
	sort(G, G + 2 * n);
	iG = unique(G, G + 2 * n) - G;
	for (int i = 0; i < 2 * n; i++) ind[i] = lower_bound(G, G + iG, A[i]) - G;
	
	ll ans = 0;
	T.clear();
	for (int i = start * 2 + 1; i < 2 * n; i++) T.upd(1, 0, iG, ind[i], 1, A[i]);	
	st = 2 * start + 1;
	dfs(0, d, 2 * start + 1, 2 * n - 1, goR);
	T.clear();
	
	copy(attraction, attraction + n, A);
	copy(A, A + n, G);
	sort(G, G + n);
	iG = unique(G, G + n) - G;
	for (ll i = 0; i < n; i++) ind[i] = lower_bound(G, G + iG, A[i]) - G;
	
	reverse(A, A + n);
	reverse(ind, ind + n);
	
	st = n - start - 1;
	
	for (ll i = st + 1; i < n; i++) T.upd(1, 0, iG, ind[i], 1, A[i]);	
	dfs(0, d, st + 1, n - 1, goL);
	
	/*for (int i = 0; i <= d; i++) {
		err("goL[%d] = (%lld, %lld)\n", i, goL[i].first, goL[i].second);
	}*/
	
	for (int i = 0; i <= d; i++) {
		int t = goR[i].first;
		if (t % 2 == 0) t--;
		int k = d - i;
		if (k >= 0) {
			ans = max(ans, goR[i].second + goL[k].second);
		}
	}
	return ans;
}

ll findMaxAttraction(int n, int start, int d, int attraction[]) {
	ll ans = calc1(n, start, d, attraction);
	ans = max(ans, calc2(n, start, d, attraction));
	reverse(attraction, attraction + n);
	start = n - start - 1;
	
	ans = max(ans, calc2(n, start, d, attraction));
	return ans;
}
