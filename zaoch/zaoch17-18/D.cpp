#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;
ll h[dd], v[dd];
int n, H, T;

void make(ll &x) {
	for (int i = n - 1; i >= 0; i--) {
		if (x >= h[i]) x = max(x - v[i], h[i] - 1);
	}
}

bool check(ll x) {
	ll cur = 0;
	for (int it = 0; it < T; it++) {
		cur += x;
		make(cur);
		if (cur >= H) return true;
	}
	return false;
}

int main() {
	cin >> n >> H >> T;
	for (int i = 0; i < n; i++) cin >> h[i] >> v[i];
	ll l = -1, r = (ll)1e16;
	while (r - l > 1) {
		ll m = (l + r) / 2;
		if (check(m)) r = m;
		else l = m;
	}
	cout << r << "\n";	
	return 0;
}