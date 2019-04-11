#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int t; cin >> t;
	
	while (t--) {
		ll a, b;
		cin >> a >> b;
		
		int ok = 0;
		
		if (a - b == 1) {
			ll x = a + b;
			ok = 1;
			for (ll i = 2; i * i <= x; i++) {
				if (x % i == 0) {
					ok = 0;
					break;
				}
			}
		}
		puts(ok ? "YES" : "NO");
		
	}
	return 0;
}