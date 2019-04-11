#include <bits/stdc++.h>
#define ll long long

using namespace std;

struct req {
	int x, f, tp;
	bool operator < (req b) const {
		return x == b.x ? tp < b.tp : x < b.x;
	}
};

const int dd = 1e5 + 7;

struct fen {
	ll T[dd];
	void upd(int v, int val) {
		for (int i = v + 1; i < dd; i += (i&-i))
			T[i] += val;
	}
	ll get(int v) {
		ll res = 0;
		for (int i = v + 1; i; i -= (i&-i))
			res += T[i];
		return res;
	}
	ll get(int l, int r) {
		return get(r) - get(l - 1);
	}
} J, R;

int n, S;

int maxS = (int)1e5 + 2;

int get(int S, int x, int nxt) {
	int l = -1, r = S;
	while (r - l > 1) {
		int m = (l + r) / 2;
		
		if (S * 1.0 / (m + 1) >= x)
			l = m;
		else
			r = m;
	}
	r = l;
	if (S * 1.0 / (r + 1) >= x && (nxt == -1 || S * 1.0 / (r + 1) <= nxt))
		return r;
	return -1;
}

ll get(int x, int nxt) {
	int k = get(S, x, nxt);
	
	if (k == -1)
		return 0;

	int l = 0, r = maxS;
	
	while (r - l > 1) {
		int m = (l + r) / 2;
		
		if (J.get(m, maxS) >= k)
			l = m;
		else
			r = m;
	}
	
	ll ans = (k - J.get(r, maxS)) * l;
	ans += R.get(r, maxS);
	return ans;
}

int main() {
#ifndef HOME
	freopen("party.in", "r", stdin);
	freopen("party.out", "w", stdout);
#endif
	scanf("%d %d", &n, &S);
	
	vector<req> T;
	vector<pair<int, int> > A(n);
	vector<int> F(n);
		
	for (int i = 0; i < n; i++) {
		int a, b, f;
		scanf("%d %d %d", &a, &b, &f);
		T.push_back({ a, f, 0 });
		T.push_back({ b, f, 1 });
		A[i] = { a, b };
		F[i] = f;
	}
	
	sort(T.begin(), T.end());
		
	vector<ll> H((int)T.size());
		
	for (int i = 0; i < (int)T.size(); i++) {
		auto c = T[i];
		if (c.tp == 0) {
			J.upd(c.f, 1);
			R.upd(c.f, c.f);
		} else {
			J.upd(c.f, -1);
			R.upd(c.f, -c.f);
		}
		if (i + 1 < (int)T.size())
			H[i] = get(c.x, T[i + 1].x);
	}	
	
	int ind = max_element(H.begin(), H.end() - 1) - H.begin();
	
	int k = get(S, T[ind].x, T[ind + 1].x);
	printf("%d %lld\n", k, H[ind]);
	
	vector<pair<int, int> > res;
	for (int i = 0; i < n; i++) {
		if (S >= A[i].first * (k + 1) && S <= A[i].second * (k + 1))
			res.push_back({ F[i], i });
	}
	
	sort(res.rbegin(), res.rend());
	for (int i = 0; i < k; i++)
		printf("%d ", res[i].second + 1);
	return 0;
}
