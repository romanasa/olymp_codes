#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	vector<int> A(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	
	sort(A.begin(), A.end());
	
	int l = (A.size() - 1) / 2, r = l + 1;
	
	vector<int> ans(n);
	
	for (int i = 0; i < n; i += 2) {
		if (l >= 0) ans[i] = A[l--];
		if (r < n) ans[i + 1] = A[r++];
	}
	
	
	for (int i = 0; i < n; i++) cout << ans[i] << " ";
	return 0;
}