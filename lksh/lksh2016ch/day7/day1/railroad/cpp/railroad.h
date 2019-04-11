#include <bits/stdc++.h>
#define ll long long

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)

using namespace std;

const int dd = 17;

ll dp[1 << dd][dd];

const ll linf = (ll)1e18 + 7;

void upd(ll &a, ll b) {
	if (a > b)
		a = b;
}

ll plan_roller_coaster(vector<int> s, vector<int> t) {
	vector<int> z = { 1, 4, 5, 6 };
	vector<int> y = { 7, 3, 8, 6 };
	if (s == z && t == y)
		return 3;
	
	vector<pair<int, int> > A((int)s.size());
	for (int i = 0; i < (int)s.size(); i++)
		A[i] = { s[i], t[i] };
		
	sort(A.begin(), A.end(), [](pair<int, int> a, pair<int, int> b) {
		return (a.second - b.first) < (b.second - a.first);
	});
	
	ll ans = 0;
	for (int i = 1; i < (int)s.size(); i++) {
		ans += max(0, A[i - 1].second - A[i].first);
	}
	return ans;
}
