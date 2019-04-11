#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = 998244353;

int C[2007][2007];
int fact[2007];

#define TASK "permutations7"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, k;
	cin >> n >> k;
	
	fact[0] = 1;
	for (int i = 1; i <= n; i++) fact[i] = 1ll * fact[i - 1] * i % mod;

	for (int i = 0; i <= n; i++) C[0][0] = 0;
	for (int i = 0; i <= n; i++) C[i][0] = 1;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}
	}
	
	
	vector<int> T(n);
	
	for (int i = n - 1; i >= k; i--) {
		T[i] = 1ll * C[n - 1][i] * fact[n - i] % mod;
		
		for (int j = i + 1; j <= n - 1; j++) {
			T[i] -= 1ll * T[j] * C[j][i] % mod;
			if (T[i] < 0) T[i] += mod;
		}
	}
	
	cout << T[k] << "\n";
	
	

	return 0;
}