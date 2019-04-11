#include <bits/stdc++.h>
#define ll long long

using namespace std;

#define TASK "spaceship"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	
	vector<int> A(n);
	for (int i = 0; i < n; i++) scanf("%d", &A[i]);
	
	ll sum = accumulate(A.begin(), A.end(), 0ll);
	
	for (int i = 0; i < n; i++) {
		if (sum - A[i] == A[i]) {
			for (int j = 0; j < n; j++) if (i != j)
				printf("%d ", A[j]);
			printf("%d\n", A[i]);
			return 0;
		}
	}
	
	return 0;
}