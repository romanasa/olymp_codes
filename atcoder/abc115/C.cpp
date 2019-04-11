#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, k;
	cin >> n >> k;
	
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	sort(a.begin(), a.end());
	
	int ans = (int)1e9 + 7;
	for (int i = 0; i + k <= n; i++) ans = min(ans, a[i + k - 1] - a[i]);
	cout << ans << "\n";
	return 0;
}