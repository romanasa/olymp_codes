#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1234;

int A[dd][dd];
int P[dd][dd];
int nxt[dd], prv[dd];
int st[dd], sz, ind[dd];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &A[i][j]);
		}
	}
	
	for (int i = 0; i < n - 1; i++) {
		int k = 1;
		
		for (int j = 0; j < m - 1; j++) {
			while (j + k < m && A[i][j + k - 1] - A[i + 1][j + k - 1] <= A[i][j + k] - A[i + 1][j + k]) {
				k++;
			}
			P[i][j] = k;
			if (k > 1) k--;
			//err("%d%c", P[i][j], " \n"[j == m - 2]);
		}
	}
	
	int ans = 0;
	
	for (int j = 0; j < m - 1; j++) {
		sz = 0;
		for (int i = 0; i < n - 1; i++) {
			while (sz && st[sz - 1] >= P[i][j]) sz--;
			prv[i] = (sz ? ind[sz - 1] : -1);
			st[sz] = P[i][j], ind[sz] = i;
			sz++;
		}
		
		sz = 0;
		for (int i = n - 2; i >= 0; i--) {
			while (sz && st[sz - 1] >= P[i][j]) sz--;
			nxt[i] = (sz ? ind[sz - 1] : n - 1);
			st[sz] = P[i][j], ind[sz] = i;
			sz++;
		}
		
		for (int i = 0; i < n - 1; i++) {
			ans = max(ans, (nxt[i] - prv[i]) * P[i][j]);
		}
	}
	
	printf("%d\n", ans);
	return 0;
}