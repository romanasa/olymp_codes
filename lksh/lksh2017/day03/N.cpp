#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, k;
	cin >> n >> k;
	
	vector<int> A(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	
	sort(A.begin(), A.end());
	for (int i = 0; i < n; i++) {
		k += A[i];
	}
	printf("%d\n", k);
	return 0;
}