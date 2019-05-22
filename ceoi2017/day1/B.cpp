#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	
	vector<double> A(n), B(n), pA(n + 1), pB(n + 1);
	for (int i = 0; i < n; i++) {
		cin >> A[i] >> B[i];
		A[i]--, B[i]--;
	}
	
	sort(A.rbegin(), A.rend());
	sort(B.rbegin(), B.rend());
	
	for (int i = 0; i < n; i++) {
		pA[i + 1] = A[i] + pA[i];
	}
	
	for (int i = 0; i < n; i++) {
		pB[i + 1] = B[i] + pB[i];
	}
	
	double ans = 0;
	for (int a = 0; a <= n; a++) {
		for (int b = 0; a + b <= n; b++) {
			ans = max(ans, min(pA[a] - b, pB[b] - a));
		}
	}
	
	cout.precision(5);
	cout << fixed << ans << "\n";
	
	return 0;
}