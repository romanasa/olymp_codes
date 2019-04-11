#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	string s, t;
	cin >> s >> t;
	
	int n = (int)s.size();
	int m = (int)t.size();
	
	vector<vector<int> > nxt(n + 1, vector<int>(131, n));
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < 131; j++) nxt[i][j] = nxt[i + 1][j];
		nxt[i][(int)s[i]] = i;
	}
	
	vector<vector<int> > dp(n + 1, vector<int>(m + 1, (int)1e9));
	vector<vector<int> > p(n + 1, vector<int>(m + 1, -1));
	
	dp[0][0] = 0;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			
			if (dp[i][j] == (int)1e9) continue;
			
			if (i < n && dp[i + 1][j] > dp[i][j] + 1) {
				dp[i + 1][j] = dp[i][j] + 1;
				p[i + 1][j] = -2;
			}
			
			if (j == m) continue;
			
			int c = t[j];
			if (i < n && nxt[i][c] > i && dp[i + 1][j] > dp[i][j]) {
				dp[i + 1][j] = dp[i][j];
				p[i + 1][j] = -3;
			}
			
			if (dp[min(nxt[i][c] + 1, n)][j + 1] > dp[i][j]) {
				dp[min(nxt[i][c] + 1, n)][j + 1] = dp[i][j];
				p[min(nxt[i][c] + 1, n)][j + 1] = i;
			}
		}
	}
	
	int ii = -1, jj = -1;
	int ans = (int)1e9;
	
	for (int j = 0; j < m; j++) {
		if (ans > dp[n][j]) ans = dp[n][j], ii = n, jj = j;
	}
	//cout << ans << "\n";
	
	vector<int> bl(n + 1);
	while (p[ii][jj] != -1) {
		int t = p[ii][jj];
		 
		if (t == -2) bl[ii] = 1, ii--;
		else if (t == -3) ii--; 
		else {
			jj--;
			ii = t;
		}
	}
	
	for (int i = 0; i < n; i++) if (!bl[i + 1]) cout << s[i];
	cout << "\n";

	return 0;
}