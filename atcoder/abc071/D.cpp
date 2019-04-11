#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = (int)1e9 + 7;

int dp[123][3][3];

int main() {	
	int n;
	cin >> n;
	
	string s1, s2;
	cin >> s1 >> s2;
	
	for (int c1 = 0; c1 < 3; c1++) {
		for (int c2 = 0; c2 < 3; c2++) {
			if ((s1[0] == s2[0]) ^ (c1 == c2)) continue;
			dp[0][c1][c2] = 1;
		}
	}
	
	for (int i = 0; i + 1 < n; i++) {
		for (int c1 = 0; c1 < 3; c1++) {
			for (int c2 = 0; c2 < 3; c2++) {
				if (dp[i][c1][c2] == 0) continue;
				for (int t1 = 0; t1 < 3; t1++) {
					for (int t2 = 0; t2 < 3; t2++) {
						if ((s1[i] == s1[i + 1]) ^ (c1 == t1)) continue;
						if ((s2[i] == s2[i + 1]) ^ (c2 == t2)) continue;
						if ((s1[i + 1] == s2[i + 1]) ^ (t1 == t2)) continue;
						
						dp[i + 1][t1][t2] += dp[i][c1][c2];
						if (dp[i + 1][t1][t2] >= mod) dp[i + 1][t1][t2] -= mod;
					}
				}
			
			}
		}
	}
	int ans = 0;
	for (int c1 = 0; c1 < 3; c1++) {
		for (int c2 = 0; c2 < 3; c2++) {
			ans += dp[n - 1][c1][c2];
			if (ans >= mod) ans -= mod;
		}
	}
	cout << ans << "\n";
	return 0;
}