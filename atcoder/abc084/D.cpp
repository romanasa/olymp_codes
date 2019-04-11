#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

bool prime(int x) {
	if (x <= 1) return false;
	for (int i = 2; i * i <= x; i++) if (x % i == 0) return false;
	return true;
}

int main() {
	for (int x = 1; x <= 1000; x++) if (prime(x) && prime(2 * x - 1))
		cout << 2 * x - 1 << ", ";

	return 0;
}