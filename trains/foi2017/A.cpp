#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, x;
	cin >> n >> x;
	
	vector<pair<int, int> > A(n);
	for (int i = 0; i < n; i++) cin >> A[i].first >> A[i].second;
	sort(A.begin(), A.end());
	
	for (int i = 1; i < n; i++) A[i].second = max(A[i].second, A[i - 1].second);
	
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int t = x - A[i].first;
		if (t < 0) continue;
		int ind = lower_bound(A.begin(), A.end(), make_pair(t, (int)1e9)) - A.begin() - 1;
		if (ind >= 0) ans = max(ans, A[i].second + A[ind].second);
	}
	cout << ans << "\n";
	
	return 0;
}