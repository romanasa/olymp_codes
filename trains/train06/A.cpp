#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

#define TASK "swap"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, q;
	scanf("%d %d", &n, &q);
	
	vector<int> A(2 * n);
	for (int i = 0; i < 2 * n; i++) A[i] = i;
	int cnt = n;
	
	while (q--) {
		int i, j;
		scanf("%d %d", &i, &j);
		
		i--, j--;
		//err("i = %d, j = %d, n = %d, A[i] = %d, A[j] = %d\n", i, j, n, A[i], A[j]);
		if (i < n && j >= n) cnt = cnt - (A[i] < n) + (A[j] < n);
		if (j < n && i >= n) cnt = cnt - (A[j] < n) + (A[i] < n);
		
		swap(A[i], A[j]);
		
		printf("%d\n", cnt);
	}
	return 0;
}