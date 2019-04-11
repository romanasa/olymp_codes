#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> A(n), T;
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		if (i) T.push_back(A[i] - A[i - 1] - 1);
	}
	int ans = A[n - 1] - A[0] + 1;
	sort(T.rbegin(), T.rend());
	for (int i = 0; i < k - 1; i++) ans -= T[i];
	cout << ans << "\n";
	return 0;
}