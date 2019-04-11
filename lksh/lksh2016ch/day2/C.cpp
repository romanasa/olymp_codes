#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

const int dd = 4000 + 7;
const ll linf = (ll)2e18 + 7;

ll dist(ll a, ll b) {
	return abs(a - b);
}

ll dp[dd][dd];
int p[dd][dd];

void upd(ll &a, ll b) {
	if (a > b)
		a = b;
}

pair<int, int> A[dd], B[dd];

int main() {
#ifndef HOME
	freopen("evacuation.in", "r", stdin);
	freopen("evacuation.out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	
	
	map<int, int> M, N;
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i].first);
		A[i].second = i;
	}
	
	int m;
	scanf("%d", &m);
	
	for (int i = 0; i < m; i++) {
		scanf("%d", &B[i].first);
		B[i].second = i;
	}
	
	sort(A, A + n);
	sort(B, B + m);

	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)	
			dp[i][j] = linf;
	dp[0][0] = 0;
	
	for (int j = 0; j <= m; j++) {
		
		for (int i = 0; i <= n; i++)	{
			
			if (i < n && j < m)
				if (dp[i + 1][j + 1] > dp[i][j] + dist(A[i].first, B[j].first)) {
					dp[i + 1][j + 1] = dp[i][j] + dist(A[i].first, B[j].first);
					p[i + 1][j + 1] = j;
				}
			
			if (j && dp[i + 1][j] > dp[i][j] + dist(A[i].first, B[j - 1].first)) {
				dp[i + 1][j] = dp[i][j] + dist(A[i].first, B[j - 1].first);
				p[i + 1][j] = j;
			}
		}
	}
	printf("%lld\n", dp[n][m]);
	
	vector<int> ans(n);
	
	int j = m;
	for (int i = n; i > 0; i--) {
		ans[A[i - 1].second] = B[j - 1].second;
		j = p[i][j];
	}
	
	for (int x : ans)
		printf("%d ", x + 1);
	return 0;
}
