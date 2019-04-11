#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)3e3 + 7;
int dp[dd][dd];
int P[dd][dd], S[dd][dd];

int main() {
	int n, r;
	cin >> n >> r;
	
	vector<int> A(n + 1);
	vector<int> id(n + 1);
	
	for (int i = 0; i < n; i++) cin >> A[i + 1];
	for (int i = 0; i <= n + 2; i++) fill(dp[i], dp[i] + n, -1e9);
	for (int i = 1; i <= n - 1; i++) dp[1][i] = 0;
	
	for (int i = 1; i <= n; i++) {
		
		for (int a = 1; a <= n - 1; a++) {	
			int ind1 = a - (i - 1) * r;
			ind1 %= n;
			while (ind1 < 1) ind1 += n;
			
			if (dp[i][a] == -1e9) P[i][a] = -1;
			else P[i][a] = dp[i][a] + A[ind1];
			if (a > 1) P[i][a] = max(P[i][a], P[i][a - 1]);
		}
		
		for (int b = 1; b <= n - 1; b++) {
			int ind2 = b + 1 - (i - 1) * r;
			ind2 %= n;
			while (ind2 < 1) ind2 += n;
			
			if (P[i][b] == -1e9) continue;
			dp[i + 1][b] = max(dp[i + 1][b], P[i][b] - A[ind2]);
		}
		
		for (int a = n - 1; a >= 1; a--) {
		
			int ind2 = a + 1 - (i - 1) * r;
			ind2 %= n;
			while (ind2 < 1) ind2 += n;
			
			if (dp[i][a] == -1e9) S[i][a] = -1;
			else S[i][a] = dp[i][a] - A[ind2];
			if (a + 1 <= n - 1) S[i][a] = max(S[i][a], S[i][a + 1]);
		}
	
		for (int b = 1; b <= n - 1; b++) {
		
			int ind1 = b - (i - 1) * r;
			ind1 %= n;
			while (ind1 < 1) ind1 += n;
			
			if (S[i][b] == -1e9) continue;
			dp[i + 1][b] = max(dp[i + 1][b], S[i][b] + A[ind1]);
		}
	}
	
	/*for (int i = 1; i <= n + 1; i++) {
		for (int j = 1; j <= n - 1; j++) {
			err("dp[%d][%d] = %d,%c", i, j, dp[i][j], " \n"[j == n - 1]);
		}
	}*/
	
	printf("%d\n", *max_element(dp[n + 1] + 1, dp[n + 1] + n));
	
	return 0;
}