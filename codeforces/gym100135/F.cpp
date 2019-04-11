#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int S = (int)3e5 + 1;
const int C = 1000;

int dp[S];

int main() {
	vector<int> a;
	for (int i = 1; i < C; i++) a.push_back((a.size() ? a.back() : 0) + 1ll * i * (i + 1) / 2);
	//cout << a.back() << "\n";
	
	fill(dp, dp + S, (int)1e9);
	dp[0] = 0;
	
	for (int x : a) for (int j = x; j < S; j++) dp[j] = min(dp[j], dp[j - x] + 1);
	
	int t;
	cin >> t;
	while (t--) {
		int x;
		cin >> x;
		cout << dp[x] << "\n";
	}
	
	return 0;
}