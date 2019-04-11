#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

ll bp(ll a, ll n) {
	ll res = 1;
	for (int i = 0; i < n; i++) res *= a;
	return res;
}

int main() {
	int n;
	cin >> n;
	while (n--) {
		ll x;
		cin >> x;
		if ((x & 1) == 0) puts("IMPOSSIBLE");
		else {
			ll y = 1- x;
			cout << (1 + y) * (1 + bp(y, 2)) * (1 + bp(y, 4)) * (1 + bp(y, 8)) * (1 + bp(y, 16)) * (1 + bp(y, 32)) << "\n";
		}
	} 
	return 0;
}