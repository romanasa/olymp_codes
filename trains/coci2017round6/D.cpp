#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	
	vector<pair<int, int> > T(n), Q;
	vector<ll> dp(n + 1);
	
	for (int i = 0; i < n; i++) {
		cin >> T[i].first >> T[i].second;
		T[i].first = abs(T[i].first);
		T[i].second = abs(T[i].second);
	}
	
	sort(T.begin(), T.end());
	for (auto c : T) {
		while (Q.size() && Q.back().second <= c.second) Q.pop_back();
		Q.push_back(c);
	}
	
	n = (int)Q.size();
	for (int i = 1; i <= n; i++) {
		dp[i] = (ll)1e18;
		for (int j = 0; j < i; j++) {
			dp[i] = min(dp[i], dp[j] + 1ll * Q[j].second * Q[i - 1].first);
		}
	}
	cout << dp[n] * 4 << "\n";
	return 0;
}