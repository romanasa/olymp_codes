#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int a[123];
int ans = 0;

void get(int l, int r, int last) {
	if (l > r) return;
	int mn = l;
	for (int i = l; i <= r; i++) {
		if (a[i] < a[mn]) mn = i;
	}
	
	ans += (a[mn] - last);
	get(l, mn - 1, a[mn]);
	get(mn + 1, r, a[mn]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	get(0, n - 1, 0);
	cout << ans << "\n";
	return 0;
}