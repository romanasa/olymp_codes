#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	
	vector<pair<ll, ll> > T(n);
	for (int i = 0; i < n; i++) cin >> T[i].first >> T[i].second;
	
	sort(T.begin(), T.end());
	
	vector<ll> P(n);
	for (int i = 0; i < n; i++) {
		P[i] = T[i].second;
		if (i) P[i] += P[i - 1];
	} 

	ll cur = -(ll)1e18;	
	ll ans = -(ll)1e18;
	for (int i = 0; i < n; i++) {
		cur = max(cur, T[i].first - (i ? P[i - 1] : 0ll));
		ans = max(ans, P[i] - T[i].first + cur);
	}
	cout << ans << "\n";
	return 0;
}