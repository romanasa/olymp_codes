#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 107;

int n, m, k;

bool ok(int i, int j) { return i >= 0 && i < n && j >= 0 && j < m; }

int pr[dd][dd];
int a[dd][dd];

int dp[11][11][101][4][730];

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

int calc(int i, int j, int len, int last, int msk) {
	if (len == k - 1) return a[i][j];
	int &cur = dp[i][j][len][last][msk];
	if (cur != -1) return cur;
	cur = -32000;
	int old = pr[i][j];
	pr[i][j] = len;
	for (int d = 0; d < 4; d++) {
		if (len > 0 && last == d) continue;
		int ni = i + dx[d], nj = j + dy[d];
		if (!ok(ni, nj)) continue;
		int t = len - pr[ni][nj];
		if (t < 30 && (1 << (t - 1)) < a[ni][nj]) continue;
		int nlast = (d + 2) % 4;
		int nmsk = msk / 3 + (len ? 1 : 0) * 243 * (last < d ? last : last - 1);
		cur = max(cur, calc(ni, nj, len + 1, nlast, nmsk) + a[i][j]);
	}
	pr[i][j] = old;
	return cur;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif
	memset(dp, -1, sizeof(dp));
	memset(pr, -11, sizeof(pr));
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> a[i][j];
	cout << calc(0, 0, 0, 0, 0) << "\n";
    return 0;
}
