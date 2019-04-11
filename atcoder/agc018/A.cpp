#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> A(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	
	int t = 0;
	for (int i = 0; i < n; i++) t = __gcd(t, A[i]);
	
	if (k % t == 0 && k <= *max_element(A.begin(), A.end())) puts("POSSIBLE");
	else puts("IMPOSSIBLE");
	return 0;
}