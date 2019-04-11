#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int a, b, k;
	cin >> a >> b >> k;
	
	int ans = 0;
	for (int x = a; x <= b; x++) {
		int ok = 1;
		for (int j = 2; j < k; j++) if (x % j == 0) {
			ok = 0;
			break;
		}
		ans += ok;
	}
	cout << ans << "\n";
	return 0;
}