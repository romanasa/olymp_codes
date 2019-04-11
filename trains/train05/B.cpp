#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const int dd = (int)2e5 + 1;

int A[dd], prv[dd];
pair<ll, int> P[dd];
map<int, int> pos;

struct FenwickTree {
	int T[dd];
	void upd(int pos, int val) {
		for (int i = pos + 1; i < dd; i += (i&-i))
			T[i] += val;
	}
	int get(int pos) {
		int res = 0;
		for (int i = pos + 1; i; i -= (i&-i))
			res += T[i];
		return res;
	}
	int get(int l, int r) {
		return get(r) - get(l - 1);
	}
} F;

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}
	
	for (int i = 0; i < n; i++) {
		auto it = pos.find(A[i]);
		if (it != pos.end()) F.upd(it->second, -1);
		pos[A[i]] = i;
		F.upd(i, 1);
		
		if (F.get(0, i) < k) prv[i] = -1;
		else {
			int l = 0, r = i + 1;
			while (r - l > 1) {
				int m = (l + r) / 2;
				if (F.get(m, i) >= k) l = m;
				else r = m;
			}
			prv[i] = l;
		}
	}
	
	ll sum = 0;
	ll ans = -(ll)1e18;
	int ii = -1, jj = -1;
	
	for (int i = 0; i < n; i++) {
		sum += A[i];
		P[i + 1] = min(P[i], make_pair(sum, i + 1));
		//err("(%I64d, %d)\n", P[i].first, P[i].second);
		if (prv[i] == -1) continue;
		ll cur = sum - P[prv[i]].first;
		if (cur > ans) {
			ans = cur;
			ii = P[prv[i]].second;
			jj = i;
		}
	}
	if (ans != -(ll)1e18) printf("%I64d\n%d %d\n", ans, ii + 1, jj + 1);
	else puts("IMPOSSIBLE");
	return 0;
}