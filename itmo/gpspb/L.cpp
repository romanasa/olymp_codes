#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

#define TASK "xorsep"

int main() {
	int n; cin >> n;
	
	vector<ll> A(n);
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}
	
	ll t = 0;
	for (ll x : A) t ^= x;
	if (t != 0) {
		cout << 0 << "\n";
	} else {
		cout << (1ll << n) - 2;
	}
	return 0;
}