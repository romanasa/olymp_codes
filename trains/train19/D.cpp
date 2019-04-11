#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	unordered_set<ll> ans;

	vector<ll> cur(1), ncur;
	
	for (int i = 0; i < n; i++) {
		ll t;
		cin >> t;
		
		for (auto x : cur) ncur.push_back(__gcd(x, t));
		ncur.push_back(t);
		
		sort(ncur.begin(), ncur.end());
		ncur.resize(unique(ncur.begin(), ncur.end()) - ncur.begin());
		cur = ncur, ncur.clear();
		
		for (auto x : cur) ans.insert(x);
	}
	cout << ans.size() << "\n";
	return 0;
}