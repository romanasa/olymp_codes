#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = (int)1e9 + 7;

int T[1007][1007];
int G[1007];

int main() {

	T[0][0] = 1;
	for (int i = 1; i <= 1000; i++) {
		for (int j = 1; j <= i; j++) {
			T[i][j] = T[i - 1][j - 1] + 1ll * T[i - 1][j] * j % mod;
			if (T[i][j] >= mod) T[i][j] -= mod;
			G[i] += T[i][j];
			if (G[i] >= mod) G[i] -= mod;
		}
	}

	int m, n;
	cin >> m >> n;
	
	vector<string> A(m);
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < m; j++) A[j] += s[j];
	}
	
	sort(A.begin(), A.end());
	
	
	int ans = 1;
	for (int i = 0; i < m; ) {
		int j = i;
		while (j < m && A[i] == A[j]) j++;
		ans = 1ll * ans * G[j - i] % mod;
		i = j;
	}
	cout << ans << "\n";

	return 0;
}