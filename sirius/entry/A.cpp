#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const int dd = 107;
ll dp[dd][dd];
int p[dd][dd];

int main() {
	int n;
	scanf("%d", &n);
	
	dp[0][0] = 1;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= n; j++) {
			if (!dp[i][j]) continue;
			for (int k = j + 1; i + k <= n; k++) {
				if (dp[i + k][k] < dp[i][j] * k) {
					dp[i + k][k] = dp[i][j] * k;
					p[i + k][k] = j;
				}
			}
		}
	}
	
	ll ans = -1;
	int j = -1;
	for (int i = 1; i <= n; i++) {
		if (dp[n][i] > ans) {
			ans = dp[n][i];
			j = i;
		}
	}
	
	int i = n;
	deque<int> A;
	while (i) {
		A.push_front(j);
		int ni = i - j, nj = p[i][j];
		i = ni, j = nj;	
	}
	for (int x : A) printf("%d ", x);
	return 0;
}