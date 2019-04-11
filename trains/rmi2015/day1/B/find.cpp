#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int N = (1 << 17);

const int mod = 2999;

int bp(int a, int n) {
	if (n == 0) return 1;
	if (n & 1) return bp(a, n - 1) * a % mod;
	int t = bp(a, n / 2);
	return t * t % mod;
}

bool check(int x) {
	if (bp(x, N) != 1) return false;
	for (int k = 1; k < N; k++) if (bp(x, k) == 1) return false;
	return true;
}

int main() {


	for (int root = 2; ;root++) {
		if (check(root)) {
			cout << root << "\n";
			break;
		}
		err("root = %d\n", root);
	}

	return 0;
}