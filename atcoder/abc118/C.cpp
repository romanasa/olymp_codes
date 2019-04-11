#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n; cin >> n;
	int t = 0;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		t = __gcd(t, x);
	}
	cout << t << "\n";
	return 0;
}