#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	vector<int> A(n), B(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	for (int i = 0; i < n; i++) cin >> B[i];
	
	ll s1 = 0, s2 = 0;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		s1 += A[i], s2 += B[i];
		if (s1 == s2) {
			ans = i + 1;
		}
	}
	cout << ans << "\n";
	return 0;
}