#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	
	vector<int> A(n);
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		A[i]--;
	}
	
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (A[i] != i) continue;
		if (i + 1 < n) swap(A[i], A[i + 1]);
		else swap(A[i], A[i - 1]);
		ans++;
	}
	cout << ans << "\n";
	return 0;
}