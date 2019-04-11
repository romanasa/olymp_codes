#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

map<int, int> cnt;

int main() {
	int n;
	cin >> n;
	
	vector<int> A(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	
	for (int i = 0; i < n; i++) {
		cnt[A[i] - 1]++;
		cnt[A[i]]++;
		cnt[A[i] + 1]++;
	}
	
	int ans = 0;
	for (auto c : cnt) ans = max(ans, c.second);
	cout << ans << "\n";
	return 0;
}