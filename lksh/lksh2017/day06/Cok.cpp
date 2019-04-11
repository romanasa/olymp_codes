#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	freopen("02", "r", stdin);
	
	ll x;
	cout << "A[] = {";
	while (cin >> x) {
		cout << " " << x << ", ";
	}
	cout << "}";
	return 0;
}