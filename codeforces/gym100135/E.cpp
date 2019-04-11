#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int dp[123][123];
int a[123][123];

int main() {
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) 
		for (int j = 0; j <= i; j++) cin >> a[i][j];
		
	for (int i = 0; i < n; i++) fill(dp[i], dp[i] + n + 1, (int)1e9);
		
	dp[0][0] = a[0][0];
	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			dp[i][j] = dp[i - 1][j];
			if (j) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1]);
			dp[i][j] += a[i][j];
		}
	}
	cout << *max_element(dp[n - 1], dp[n - 1] + n) << "\n";
	return 0;
}