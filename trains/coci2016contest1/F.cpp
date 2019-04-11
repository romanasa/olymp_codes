#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int cnt[21][31];
int dp[(1 << 16) + 7];
int cur[31];

int n;
	
int get(int msk) {
	fill(cur, cur + 26, (int)1e5 + 7);
	
	for (int i = 0; i < n; i++) if ((msk >> i) & 1)
		for (int j = 0; j < 26; j++) cur[j] = min(cur[j], cnt[i][j]);
		
	int len = 0;
	for (int i = 0; i < 26; i++) len += cur[i];
	return len * !!msk;
}

int calc(int msk) {
	if (dp[msk] != -1) return dp[msk];
	
	int len = get(msk);
	if ((msk&-msk) == msk) return dp[msk] = len;
	int cur = (int)1e9;
	
	for (int pmsk = (msk - 1) & msk; pmsk; pmsk = (pmsk - 1) & msk) {
		cur = min(cur, calc(pmsk) + calc(msk ^ pmsk) - len);
	}
	return dp[msk] = cur;
}


int main() {
	fill(dp, dp + (1 << 16) + 7, -1);
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (char c : s) cnt[i][c - 'a']++;
	}
	cout << calc((1 << n) - 1) + 1 << "\n";
	return 0;
}