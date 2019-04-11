#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int dp[701][701][11][2];

const int mod = (int)1e9 + 7;

void add(int &a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

int main() {
	string s;
	cin >> s;
	
	int n = (int)s.size();
	
	for (int c = 1; c <= 9; c++) dp[0][0][c][0] = 1;
	
	for (int len = 0; len < n; len++) 	
		for (int j = 0; j <= len; j++) 
			for (int c = 1; c <= 9; c++) 
				for (int t = 0; t < 2; t++) if (dp[len][j][c][t]) 
					for (int q = 0; q <= (t ? 9 : s[len] - '0'); q++) 
						add(dp[len + 1][j + (q < c)][c][t | (q < r)], dp[len][j][c][t]);
	
	int ans = 0;
	for (int c = 1; c <= 9; c++) {
		int p = 1;
		for (int pos = n - 1, p = 1; pos >= 0; pos--) {
			int cnt = 0;
			for (int q = pos; q >= 0; q--) 	
				add(cnt, dp[n][q][c][0]), add(cnt, dp[n][q][c][1]);
			
			add(ans, 1ll * cnt * p % mod), p = 1ll * p * 10 % mod;
		}
	}
	cout << ans << "\n";
	return 0;
}