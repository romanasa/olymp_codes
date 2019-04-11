#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int bp(int a, int n, int mod) {
	if (!n) return 1;
	if (n & 1) return 1ll * bp(a, n - 1, mod) * a % mod;
	int t = bp(a, n / 2, mod);
	return 1ll * t * t % mod;
}

int N = 1 << 17;
 
int generator (int p) {

	for (int res=2; res<=p; ++res) {
		
		//cout << res << "\n";
		if (bp(res, N, p) != 1) continue;
		
		int ok = 1;
		for (int q = 1; q < N; q++) {
			if (bp(res, q, p) == 1) {
				ok = 0;
				break;
			}
		}
		
		if (ok) {
			return res;
		}
	
	}
	return -1;
}
int main() {
	int n;
	cin >> n;
	cout << generator(n) << "\n";
	return 0;
}