#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

bool check(ll x, vector<int> &a) {
	int n = (int)a.size();
	
	ll sum = accumulate(a.begin(), a.end(), 0ll) / 2;
	
	ll cur = 0;
	ll t = 0;
	for (int i = 0; i < n; i++) {
		ll q = max(0ll, max((cur + a[i] - x + 1) / 2, t + a[i] - sum));
		if (cur >= q) {
			cur -= q;
			cur += a[i] - q;
			t += a[i] - q;
		} else return 0;
		if (cur > x) return 0;
	}
	return 1;
}

int main() {
	int n;
	cin >> n;
	
	
	vector<int> a(n);
	vector<ll> P(n);
	
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) P[i] = (i ? P[i - 1] : 0) + a[i];
	
	
	ll ansR = -1;
	for (int i = 0; i + 1 < n; i++) {
		ll s1 = P[i];
		ll s2 = P[n - 1] - s1;
		ansR = max(ansR, min(s1, s2));
	}
	
	ll l = 0, r = ansR;
	while (r - l > 1) {
		ll m = (l + r) / 2;
		if (check(m, a)) r = m;
		else l = m;
	}
	cout << r << " " << ansR << "\n";
	return 0;
}