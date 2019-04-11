#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main() {
	int n, m;
	while (cin >> n >> m) {
		if (n == -1) break;
		
		int ok = 0;
		
		for (ll p = 1; (n + 1) * p < m + 1; p *= 2) {
			ll x = (n + 1) * p - 1;
			if (x < (m + 1) / 2 || x >= m) continue;
			ok = 1;
			cout << "H " << x << endl;
			break;
		}
		
		if (ok) continue;
		
		for (ll p = 1; (m + 1) % p == 0; p *= 2) {
			ll x = (m + 1) / p - 1;
			if (x < (n + 1) / 2 || x >= n) continue;
			ok = 1;
			cout << "V " << x << endl;
			break;
		}
		
		if (ok) continue;
		
		for (ll p = 1; (m + 1) * p < n + 1; p *= 2) {
			ll x = (m + 1) * p - 1;
			if (x < (n + 1) / 2 || x >= n) continue;
			ok = 1;
			cout << "V " << x << endl;
			break;
		}
		
		if (ok) continue;
		
		for (ll p = 1; (n + 1) % p == 0; p *= 2) {
			ll x = (n + 1) / p - 1;
			if (x < (m + 1) / 2 || x >= m) continue;
			ok = 1;
			cout << "H " << x << endl;
			break;
		}
		
	}

	return 0;
}