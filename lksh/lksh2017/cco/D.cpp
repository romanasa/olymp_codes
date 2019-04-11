#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int A[543], P[543], S[543];
set<int> can;

int main() {
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}
	
	sort(A, A + n); 
	srand(2304);
	do {
		for (int i = 0; i < n; i++) {
			P[i] = A[i];
			if (i) P[i] = max(P[i], P[i - 1]);
		}
		for (int i = n - 1; i >= 0; i--) {
			S[i] = A[i];
			if (i + 1 < n) S[i] = max(S[i], S[i + 1]);
		}
		int cur = 0;
		for (int i = 0; i < n; i++) {
			cur += max(0, min(P[i], S[i]) - A[i]);
		}
		can.insert(cur);
		random_shuffle(A, A + n);
	} while (clock() < 1.95 * CLOCKS_PER_SEC);
	for (int x : can) printf("%d ", x);
	return 0;
}