#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 7;
int b[dd], P0[dd], P1[dd];
int dp[dd];

struct SegmentTree {
	int T[4 * dd];
	
	SegmentTree() { fill(T, T + 4 * dd, (int)1e9); }
	
	void upd(int v, int tl, int tr, int pos, int val) {	
		if (tl == tr) T[v] = min(T[v], val);
		else {
			int tm = (tl + tr) / 2;
			if (pos <= tm) upd(v * 2, tl, tm, pos, val);
			else upd(v * 2 + 1, tm + 1, tr, pos, val);
			T[v] = min(T[v * 2], T[v * 2 + 1]);
		}
	}
	
	int get(int v, int tl, int tr, int l, int r) {
		if (tl == l && tr == r) return T[v];
		int tm = (tl + tr) / 2;
		if (r <= tm) return get(v * 2, tl, tm, l, r);
		if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r);
		return min(get(v * 2, tl, tm, l, tm), get(v * 2 + 1, tm + 1, tr, tm + 1, r));
	}
} T0, T1;

int main() {
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) cin >> b[i];
	for (int i = 0; i < n; i++) P0[i + 1] = P0[i] + (b[i] == 0);
	for (int i = 0; i < n; i++) P1[i + 1] = P1[i] + (b[i] == 1);
	
	int q;
	cin >> q;
	
	vector<pair<int, int> > A(q);
	for (int i = 0; i < q; i++) {
		cin >> A[i].first >> A[i].second;
		A[i].first--, A[i].second--;
	}
	sort(A.begin(), A.end());
	
	int ans = P1[n];
	
	for (int i = 0; i < q; i++) {
		dp[i] = P0[A[i].second + 1] - P0[A[i].first] + P1[A[i].first];
		if (A[i].first > 0) {
			int t = T1.get(1, 0, n - 1, 0, A[i].first - 1);
			t += P1[A[i].first] + P0[A[i].second + 1] - P0[A[i].first];
			dp[i] = min(dp[i], t);
		}
		{
			int t = T0.get(1, 0, n - 1, A[i].first, A[i].second);
			t += P0[A[i].second + 1];
			dp[i] = min(dp[i], t);
		}
		
		T0.upd(1, 0, n - 1, A[i].second, dp[i] - P0[A[i].second + 1]);
		T1.upd(1, 0, n - 1, A[i].second, dp[i] - P1[A[i].second + 1]);
	}
	
	for (int i = 0; i < q; i++) ans = min(ans, dp[i] + P1[n] - P1[A[i].second + 1]);
	cout << ans << "\n";
	return 0;
}