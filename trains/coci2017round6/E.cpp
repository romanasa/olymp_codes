#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

int sum(ll x, int b) {
	int s = 0;
	while (x) s += x % b, x /= b;
	return s;
}

map<int, vector<ll> > M;

int main() {

	int c, d, b, m;
	cin >> c >> d >> b >> m;

	for (ll index = 1; ; index += b - 1) {
		ll x = 1ll * c * index + d;
		M[sum(x, b)].push_back(index);
		if (M[sum(x, b)].size() >= m) {
			for (ll i : M[sum(x, b)]) cout << i << " ";
			return 0;
		}
	}
	return 0;
}