#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

ll get(ll x) {
	ll l = 0, r = (ll)1e9;
	while (r - l > 1) {
		ll m = (l + r) / 2;
		if (m * m <= x) l = m;
		else r = m;
	}
	return l;
}

ll solve(ll n) {
	
	ll x = n;
	vector<int> t;
	while (x) t.push_back(x % 2), x /= 2;
	
	x = (ll)1e18;
	vector<int> maxC;
	while (x) maxC.push_back(x % 2), x /= 2;
	
	reverse(maxC.begin(), maxC.end());
	reverse(t.begin(), t.end());
	
	
	sort(t.begin() + 1, t.end());
	
	ll mn = 0;
	for (int i = 0; i < (int)t.size(); i++) {
		mn = mn * 2 + t[i];
	}
	reverse(t.begin() + 1, t.end());
	t = min(t, maxC);
	
	ll mx = 0;
	for (int i = 0; i < (int)t.size(); i++) {
		mx = mx * 2 + t[i];
	}
	
	err("mn = %I64d, mx = %I64d\n", mn, mx);
	
	return get(mx) - get(mn - 1);
}

int main() {
	ll n; cin >> n;
	cout << solve(n) << "\n";
	/*
	for (int n = 1; n <= 50; n++) {
		err("F(%d) = %d\n", n, solve(n));
	}*/

	return 0;
}