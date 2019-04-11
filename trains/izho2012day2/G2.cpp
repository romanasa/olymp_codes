#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > S;

#define TASK "g"

int main() {	
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, k;
	cin >> n >> k;
	
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	
	rotate(a.begin(), max_element(a.begin(), a.end()), a.end());
	a.push_back(a[0]);
	
	vector<int> s;
	for (int i = 0; i <= n; i++) {
  		while (s.size() && a[s.back()] < a[i]) {
  			int val = a[s.back()];
  			s.pop_back();
  			S.push({ (i - s.back() - 1), min(a[s.back()], a[i]) - val });
  		}
		s.push_back(i);
	}
	
	int ans = 0;
	while (S.size()) {
		auto c = S.top();
		S.pop();
	
		int t = min(k / c.first, c.second);
		ans += t * 2;
		k -= t * c.first;
	}
	cout << ans << "\n";

	return 0;
}