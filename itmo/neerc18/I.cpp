#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

void sub(int &a, int b, int mod) {
	a -= b;
	if (a < 0) a += mod;
}

void add(int &a, int b, int mod) {
	a += b;
	if (a >= mod) a -= mod;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t, p;
	cin >> t >> p;
	
	int n = 400;
	
	vector<int> fact(n + 1);
	vector<int> I(n + 1), A(n + 1);
	vector<vector<int>> B(n + 1, vector<int>(n + 1));
	
	fact[0] = 1;
	for (int i = 1; i <= n; i++) fact[i] = 1ll * fact[i - 1] * i % p;
	
	I[0] = 1;
	for (int i = 1; i <= n; i++) {
		I[i] = fact[i];
		for (int len = 1; len < i; len++) {
			sub(I[i], 1ll * I[len] * fact[i - len] % p, p);
		}
	}
	
	B[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			for (int last = 1; last <= i; last++) {
				add(B[i][j], 1ll * B[i - last][j - 1] * fact[last] % p, p);
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		A[i] = fact[i];
		if (i > 2) for (int len = 1; len < i; len++) sub(A[i], 2ll * I[len] * fact[i - len] % p, p);
		for (int cnt = 3; cnt < i; cnt++) sub(A[i], 1ll * B[i][cnt] * A[cnt] % p, p);
	}
	
	while (t--) {
		int x; cin >> x;
		cout << A[x] << "\n";
	}
	return 0;
}