#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = (int)1e9 + 7;
const int dd = (int)2e5 + 1;

int bp(int a, int n) {
	if (n == 0) return 1;
	if (n & 1) return 1ll * bp(a, n - 1) * a % mod;
	int t = bp(a, n / 2);
	return 1ll * t * t % mod;
}

int get(int N, int K) {
	int cur = bp(K, N) - bp(K - 1, N);
	return cur < 0 ? cur + mod : cur;
}

vector<int> E[dd];

struct SegmentTree {
	int T[4 * dd];
	void build(int v, int tl, int tr, vector<int> &A) {
		if (tl == tr) T[v] = A[tl];
		else {
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm, A);
			build(v * 2 + 1, tm + 1, tr, A);
			T[v] = max(T[v * 2], T[v * 2 + 1]);
		}
	}
	int get(int v, int tl, int tr, int l, int r) {
		if (tl == l && tr == r) return T[v];
		int tm = (tl + tr) / 2;
		if (r <= tm) return get(v * 2, tl, tm, l, r);
		if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r);
		return max(get(v * 2, tl, tm, l, tm), get(v * 2 + 1, tm + 1, tr, tm + 1, r));
	}
} T;

int l[dd], r[dd], x[dd];

#define TASK "lottery"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &l[i], &r[i], &x[i]);
		l[i]--, r[i]--;
		E[l[i]].push_back(x[i]);
		E[r[i]].push_back(-x[i]);
	}
	
	vector<int> A(n);
	
	set<int> X;
	for (int i = 0; i < n; i++) {
		for (int x : E[i]) if (x > 0) X.insert(x);
		A[i] = (X.size() ? *X.begin() : (int)1e9);
		for (int x : E[i]) if (x < 0) X.erase(-x);
	}
	
	//for (int i = 0; i < n; i++) err("%d, ", A[i]); err("\n");

	T.build(1, 0, n - 1, A);
	for (int i = 0; i < m; i++) {
		if (T.get(1, 0, n - 1, l[i], r[i]) != x[i]) return 0 * puts("0");
	}

	map<int, int> cnt;
	for (int i = 0; i < n; i++) {
		cnt[A[i]]++;
	}
	
	int ans = 1;
	for (auto c : cnt) {
		if (c.first > k) ans = 1ll * ans * bp(k, c.second) % mod;
		else ans = 1ll * ans * get(c.second, c.first) % mod;
	}
	
	printf("%d\n", ans);
	return 0;
}