#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

map<int, int> cnt;

int main() {
	int n;
	cin >> n;
	vector<int> A(n);
	
	for (int i = 0; i < n; i++) cin >> A[i];
	sort(A.begin(), A.end());
	
	vector<int> p;
	int ind = -1;
	
	for (int i = 0; i < n; i++) {
		int cur = ++cnt[A[i]];
		if (cur == 4) ind = i;
		if (cur == 2) p.push_back(A[i]);
	}
	
	ll ans = 0;
	if (ind != -1) ans = max(ans, 1ll * A[ind] * A[ind]);
	if (p.size() > 1) ans = max(ans, 1ll * p.back() * p[(int)p.size() - 2]);
	cout << ans << "\n";
	
	return 0;
}