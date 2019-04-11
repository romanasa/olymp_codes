#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
#ifndef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
	ll n;
	cin >> n;
	if (n > 0) cout << n * (n + 1) / 2 << "\n";
	else cout << -n * (n - 1) / 2 + 1 << "\n";
	return 0;
}