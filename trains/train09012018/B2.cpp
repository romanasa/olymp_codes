#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, q;
	cin >> n >> q;
	vector<ll> a(n), s(n);
	for (int i = 0; i < n; i++) cin >> s[i];
	for (int it = 0, i = 0; it < n; it++, i = (i + q) % n) 
		a[(i + q) % n] = a[i] + (s[(i + 1) % n] - s[i]);
	ll add = (s[0] - accumulate(a.begin(), a.begin() + q, 0ll)) / q;
	for (int i = 0; i < n; i++) cout << a[i] + add << " "; cout << "\n";
	return 0;
}