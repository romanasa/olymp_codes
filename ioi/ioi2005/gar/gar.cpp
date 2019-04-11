#include <bits/stdc++.h>
#define ll long long
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

int A[251][251], P[251][251];
int L[251], R[251], D[251], U[251];

inline int get(int x1, int y1, int x2, int y2) {
	return P[x2][y2] - (x1 ? P[x1 - 1][y2] : 0) - (y1 ? P[x2][y1 - 1] : 0) + (x1 && y1 ? P[x1 - 1][y1 - 1] : 0);
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	int q, k;
	scanf("%d %d", &q, &k);
	
	fill(L, L + m, (int)1e9);
	fill(R, R + m, (int)1e9);
	
	fill(D, D + n, (int)1e9);
	fill(U, U + n, (int)1e9);
	
	for (int i = 0; i < q; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		A[x - 1][y - 1]++;
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			err("%d%c", A[i][j], " \n"[j == m - 1]);
			P[i][j] = (i ? P[i - 1][j] : 0) + (j ? P[i][j - 1] : 0) - (i && j ? P[i - 1][j - 1] : 0) + A[i][j];
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			
			int cur = n - 1;
			
			for (int l = j; l < m; l++) {
				while (cur >= i && get(i, j, cur, l) > k) {
					cur--;
				}
				
				while (cur >= i && get(i, j, cur, l) == k) {
					int per = 2 * (l - j + 1) + 2 * (cur - i + 1);
					
					err("(%d, %d, %d, %d) = %d\n", i, j, cur, l, get(i, j, cur, l));
					
					R[j] = min(R[j], per);
					D[i] = min(D[i], per);
					
					L[l] = min(L[l], per);
					U[cur] = min(U[cur], per);
					
					cur--;
				}
			}
		}
	}
	
	for (int j = m - 2; j >= 0; j--) {
		R[j] = min(R[j], R[j + 1]);
	}
	for (int j = 1; j < m; j++) {
		L[j] = min(L[j], L[j - 1]);
	}
	
	for (int i = n - 2; i >= 0; i--) {
		D[i] = min(D[i], D[i + 1]);
	}
	for (int i = 1; i < n; i++) {
		U[i] = min(U[i], U[i - 1]);
	}
	
	int ans = (int)1e9;
	for (int j = 0; j + 1 < m; j++) {
		ans = min(ans, L[j] + R[j + 1]);
	}	
	for (int i = 0; i + 1 < n; i++) {
		ans = min(ans, U[i] + D[i + 1]);
	}
	
	if (ans == (int)1e9)
		puts("NO");
	else
		printf("%d\n", ans);
	return 0;
}