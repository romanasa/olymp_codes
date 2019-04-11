#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	
	vector<int> A(n), cnt(4007), res(4007);
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		cnt[A[i]]++;
	}
	
	for (int len = 1; len <= 4000; len++) {
	
		for (int x = 1; x < len - x; x++) {
			res[len] += min(cnt[x], cnt[len - x]);
		}
		if (len % 2 == 0) res[len] += cnt[len / 2] / 2;
	}
	
	int ans = *max_element(res.begin(), res.end());
	
	int t = 0;
	
	for (int i = 0; i < 4007; i++) if (res[i] == ans) {
		t++;
	}
	
	cout << ans << " " << t << "\n";
	return 0;
}