#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;

	while (t--) {
		int n, k;
		cin >> n >> k;
		
		assert(k >= 23);
		
		vector<string> A(n);
		string ans(n, '0');
		
		for (int i = 0; i < n; i++) cin >> A[i];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i; j++) {
				int cnt = 0;
				for (int t = 0; t < k && cnt < 3; t++) cnt += (A[i][t] != A[j][t]);
				if (cnt < 3) ans[i] = ans[j] = '1';
			}
		}
		cout << ans << "\n";
	}
	
	return 0;
}