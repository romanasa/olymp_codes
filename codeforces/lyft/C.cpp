#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<int> > E;
vector<int> dp;

int dfs(int v) {
	if (dp[v] != -1) return dp[v];
	dp[v] = 0;
	for (int to : E[v]) {
		if (!dfs(to)) {
			dp[v] = 1;
			break;
		}
	}
	return dp[v];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n; cin >> n;
	vector<int> a(n);
	
	E.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + a[i]; j < n; j += a[i]) if (a[i] < a[j]) E[i].push_back(j);
		for (int j = i - a[i]; j >= 0; j -= a[i]) if (a[i] < a[j]) E[i].push_back(j);
	}
	dp.assign(n, -1);
	
	for (int i = 0; i < n; i++) dfs(i);
	for (int i = 0; i < n; i++) cout << (dp[i] ? 'A' : 'B');
	cout << "\n";
	
	return 0;
}