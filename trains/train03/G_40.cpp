#include <bits/stdc++.h>
#define ll long long

using namespace std;

int A[1007][1007];

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		int n, m;
		scanf("%d %d", &n, &m);
		
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &A[i][j]);
				
		int t1 = 0, t2 = 0;
		
		for (int j = 0; j < m; j++) {
			t1 += abs(A[n / 2][j] - A[n / 2 - 1][j]);
			t2 += abs(A[0][j] - A[n - 1][j]);
		}
		if (t1 > t2)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}