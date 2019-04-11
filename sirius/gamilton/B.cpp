#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int maxN = 19;
ll dp[(1 << maxN) + 1][maxN];
int p[(1 << maxN) + 1][maxN];
int A[maxN][maxN];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) scanf("%d", &A[i][j]);
	
	for (int i = 0; i < (1 << n); i++) fill(dp[i], dp[i] + n, (ll)1e18);
	
	for (int i = 0; i < n; i++) dp[(1 << i)][i] = 0;
	
	ll tmp;
	for (int msk = 0; msk < (1 << n); msk++) {
		for (int i = 0; i < n; i++) if (dp[msk][i] != (ll)1e18) {
			for (int j = 0; j < n; j++) if (((msk >> j) & 1) == 0) {
				if (dp[msk ^ (1 << j)][j] > (tmp = dp[msk][i] + A[i][j])) {
					dp[msk ^ (1 << j)][j] = tmp;
					p[msk ^ (1 << j)][j] = i;
				}
			}
		}
	}
	
	int ind = -1;
	for (int i = 0; i < n; i++) {
		if (dp[(1 << n) - 1][i] != (ll)1e18 && (ind == -1 || dp[(1 << n) - 1][i] < dp[(1 << n) - 1][ind])) {
			ind = i;
		}
	}
	
	printf("%I64d\n", dp[(1 << n) - 1][ind]);
	int cur = (1 << n) - 1;

	deque<int> ans;
	while (cur) {
		ans.push_front(ind);
		int j = p[cur][ind];
		cur ^= (1 << ind);
		ind = j;
	}	
	for (int x : ans) printf("%d ", x + 1);
	return 0;
}