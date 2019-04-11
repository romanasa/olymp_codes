#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;
int a[dd];
int b[dd];
int c[dd];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	for (int i = 0; i < n; i++) cin >> c[i];
	
	sort(a, a + n);
	sort(b, b + n);
	sort(c, c + n);
	
	
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		int ind1 = lower_bound(a, a + n, b[i]) - a;
		int ind2 = upper_bound(c, c + n, b[i]) - c - 1;
		

		if (ind1) {
			ans += 1ll * ind1 * (n - ind2 - 1);
		}
	}
	cout << ans << "\n";
	return 0;
}