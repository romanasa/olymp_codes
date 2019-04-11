#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 7;
ll a[dd], b[dd];

int n;
	
ll get(ll x) {
	int j = 0;
	ll res = 0;
	for (int i = 0; i < n; i++) {
		while (j < n && a[i] + b[j] <= x) {
			j++;
		}
		res += j;
	}
	return res;
}

#define TASK "sums-center"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	cin >> n;
	
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	
	sort(a, a + n); reverse(a, a + n);
	sort(b, b + n);
	
	ll indL = 1ll * n * (n - 1) / 2 + 1;
	ll indR = 1ll * n * (n + 1) / 2;
	
	ll l = -1, r = (ll)2e9 + 1;
	while (r - l > 1) {
		ll m = (l + r) / 2;
		if (get(m) < indL) l = m;
		else r = m;
	}
	ll start = r;
	
	l = -1, r = (ll)2e9 + 1;
	while (r - l > 1) {
		ll m = (l + r) / 2;
		if (get(m) < indR) l = m;
		else r = m;
	}
	
	ll end = r;
	if (start == end) {
		for (int i = 0; i < n; i++) cout << start << " ";
		cout << "\n";
		return 0;
	}
	
	
	int j1 = 0;
	int j2 = 0;
	vector<ll> T;
	for (int i = 0; i < n; i++) {
		while (j1 < n && a[i] + b[j1] < start + 1) j1++;
		while (j2 < n && a[i] + b[j2] <= end - 1) j2++;
		for (int j = j1; j < j2; j++) T.push_back(a[i] + b[j]);
	}
	
	
	
	ll need = get(start) - indL + 1;
	for (int i = 0; i < need; i++) T.push_back(start);
	
	while (T.size() < n) T.push_back(end);
	
	
	
	sort(T.begin(), T.end());
	for (ll x : T) cout << x << " ";
	cout << "\n";
	return 0;
}