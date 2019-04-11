#include <bits/stdc++.h>

using namespace std;

int cur = 1, t;
int c = 0;

int A[107][107];

void mark(int i, int j) {
	A[i][j] = cur;
	c++;
	
	if (c == t)
		c = 0, cur++;
}

int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	
	
	if (n * m % k > 0) {
		printf("%d\n", -1);
		return 0;
	}
	
	t = k;
	
	for (int i = 0; i < n; i++) {
		if (i % 2 == 0) {
			for (int j = 0; j < m; j++) {
				mark(i, j);
			}
		} else {
			for (int j = m - 1; j >= 0; j--) {
				mark(i, j);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			printf("%d ", A[i][j]);
		printf("\n");
	}
	return 0;
}
