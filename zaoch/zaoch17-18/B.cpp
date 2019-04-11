#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
		
	int n;
	cin >> n;
	
	ll ans = -(ll)1e18;
	int ii = -1, jj = -1;
	
	map<int, pair<ll, int> > M;
	
	ll s = 0;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		
		if (!M.count(t)) M[t] = { s, i };
		else M[t] = min(M[t], make_pair(s, i));
		
		s += t;
		ll cur = s - M[t].first;
		if (cur > ans) {
			ans = cur;
			ii = M[t].second;
			jj = i;
		}
	}
	cout << ans << "\n" << ii + 1 << " " << jj + 1 << "\n";
	return 0;
}