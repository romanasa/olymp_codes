#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	ll a, b;
	cin >> a >> b;
	
	if (a > b) swap(a, b);
	ll ans = a * a;
	ll c1 = a * a + min(a, b - a) * min(a, b - a);
	cout << max(ans, c1) << "\n";
	return 0;
}