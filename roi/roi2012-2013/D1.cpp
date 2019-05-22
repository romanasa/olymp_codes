#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

#define TASK "dynasties"

const int inf = (int)1e9 + 7;
const int dd = 1 << 18;

int dp[3][dd], p[3][dd];
int P[dd], A[3][dd], B[3][dd];
int n;

void upd(int &a, int b) {
	if (a > b)
		a = b;
}

bool ok(int i, int j, int c, int it) {
	if (i == 1 || j == n)
		return true;
	return P[j + 1] - P[i - 1] >= A[c][it] && P[j + 1] - P[i - 1] <= B[c][it];
}

int calc(int it) {
	fill(dp[0], dp[0] + n + 1, inf);
	fill(dp[1], dp[1] + n + 1, inf);
	
	dp[0][0] = 0, dp[1][0] = 0;
	
	for (int i = 1; i <= n; i++) {
		for (int c = 0; c < 2; c++) {
			
			
			for (int j = i; j <= n; j++) {
			
				if (i == j || P[j] - P[j - 1] >= A[c ^ 1][it] && P[j] - P[j - 1] <= B[c ^ 1][it]) {
					
					if (ok(i, j, c, it))
						upd(dp[c ^ 1][j], dp[c][i - 1] + j - i); 
						
				} else {
					break;
				}
			}
		}
	}
	
	//for (int i = 0; i <= n; i++)
	//	err("dp[%d][%d] = %d, dp[%d][%d] = %d\n", 0, i, dp[0][i], 1, i, dp[1][i]);
	return min(dp[0][n], dp[1][n]);
}

void rec(int it) {
	fill(dp[0], dp[0] + n + 1, inf);
	fill(dp[1], dp[1] + n + 1, inf);
	
	dp[0][0] = 0, dp[1][0] = 0;
	
	for (int i = 1; i <= n; i++) {
		for (int c = 0; c < 2; c++) {
					
			for (int j = i; j <= n; j++) {
			
				if (i == j || P[j] - P[j - 1] >= A[c ^ 1][it] && P[j] - P[j - 1] <= B[c ^ 1][it]) {
					
					if (j + 1 > n || i == 1 || P[j + 1] - P[i - 1] >= A[c][it] && P[j + 1] - P[i - 1] <= B[c][it]) {
						
						if (dp[c ^ 1][j] > dp[c][i - 1] + j - i) {
							dp[c ^ 1][j] = dp[c][i - 1] + j - i;
							p[c ^ 1][j] = i;
						}
					}
						
				} else {
					break;
				}
			}
		}
	}
	
	string ans;
	int i = n, c = (dp[0][n] < dp[1][n] ? 0 : 1);
	
	while (i > 0) {
		for (int k = i; k >= p[c][i]; k--)
			ans += (char)('1' + c);
		i = p[c][i] - 1;
		c ^= 1;
	}
	reverse(ans.begin(), ans.end());
	cout << ans;
}

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif	

	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &P[i + 1]);
	}
	
	int s;
	scanf("%d", &s);
	
	for (int i = 0; i < s; i++) {
		scanf("%d %d %d %d", &A[0][i], &B[0][i], &A[1][i], &B[1][i]);
	}
	
	int ans = inf, ind = -1;
	for (int it = 0; it < s; it++) {
		int t = calc(it);
		if (t < ans) {
			ans = t, ind = it;
		}
	}
	if (ind < 0) 
		return 0 * puts("0");
	
	printf("%d %d\n", ind + 1, ans);
	rec(ind);
	    	
	return 0;
}