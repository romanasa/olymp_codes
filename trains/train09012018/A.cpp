#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

bool prime(ll x) {
	if (x <= 1) return false;
	for (ll i = 2; i * i <= x; i++) if (x % i == 0) return false;
	return true;
}

int F(int x, int k) {
	if (x < k || !prime(k)) return 0;
	int cur = x / k;
	for (int i = 2; i < k && i <= x / k; i++)
		cur -= F(x / k, i);
	return cur;
}

int main() {
	int a, b, k;
	cin >> a >> b >> k;
	cout << F(b, k) - F(a - 1, k) << "\n";
	return 0;
}