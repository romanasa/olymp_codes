#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int dd = (int)3e4 + 7;

int w[dd], h[dd];
int bl[dd], P[dd], A[dd];
ll p1[dd], p2[dd], p3[dd];

inline void upd(ll &a, ll b) { if (a < b) a = b; }

int main() {
	
	int n, q;
	scanf("%d %d", &n, &q);

	for (int i = 0; i < n; i++) {
		scanf("%d", &w[i]);
		bl[i] = i;
		A[i] = i;
	}
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &h[i]);
		P[i] = i;
	}
	
	sort(A, A + n, [](int a, int b) { return w[a] < w[b]; });
	sort(P, P + n, [](int a, int b) { return h[a] < h[b]; });
	
	
	//err("A: "); for (int i = 0; i < n; i++) err("%d ", A[i]); err("\n");
	//err("P: "); for (int i = 0; i < n; i++) err("%d ", P[i]); err("\n");
	
	for (int i = 0; i < n; i++) {
		p1[i] = 1ll * w[A[i]] * h[P[i]];
		p2[i] = 1ll * w[A[i]] * h[P[i - 1]] + 1ll * w[A[i - 1]] * h[P[i]];
		p3[i] = max(1ll * w[A[i - 2]] * h[P[i]] + 1ll * w[A[i - 1]] * h[P[i - 2]] + 1ll * w[A[i]] * h[P[i - 1]],
						1ll * w[A[i - 2]] * h[P[i - 1]] + 1ll * w[A[i - 1]] * h[P[i]] + 1ll * w[A[i]] * h[P[i - 2]]);
	}
	
	while (q--) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--, b--;
		
		swap(bl[a], bl[b]);
		

		ll dp0 = 0, dp1 = -(ll)1e18, dp2 = -(ll)1e18;
		
		if (bl[A[0]] ^ P[0]) {
			upd(dp1, p1[0]);
		}
		
		if (bl[A[1]] ^ P[1]) {
			upd(dp2, dp1 + p1[1]);
		}
		upd(dp2, p2[1]);
		
		for (int i = 2; i < n; i++) {
			ll t = -(ll)1e18;
			if (bl[A[i]] ^ P[i]) t = dp2 + p1[i];
			if (t < dp1 + p2[i]) t = dp1 + p2[i];	
			if (t < dp0 + p3[i]) t = dp0 + p3[i];
			dp0 = dp1;
			dp1 = dp2;
			dp2 = t;
		}
		printf("%I64d\n", dp2);
	}
	return 0;
}