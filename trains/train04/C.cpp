#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int dd = 2007;

int A[dd][dd], P[dd][dd];
int used[dd][dd];
inline int get(int i1, int j1, int i2, int j2) {
	return P[i2][j2] - P[i1 - 1][j2] - P[i2][j1 - 1] + P[i1 - 1][j1 - 1];
}

int n;
	
bool ok(int i, int j) {
	return i >= 0 && i < n && j >= 0 && j < n;
}

int s = 0;

int miny, maxy, minx, maxx;

void dfs(int i, int j) {
	used[i][j] = 1;
	A[i][j] = 0;
	s++;
	minx = min(minx, i);
	miny = min(miny, j);
	maxx = max(maxx, i);
	maxy = max(maxy, j);
	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			int ni = i + dx, nj = j + dy;
			if (ok(ni, nj) && !used[ni][nj] && A[ni][nj] == 1)
				dfs(ni, nj);
		}
	}
}

int main() {
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &A[i][j]);
		}
	}
	
	for (int it = 0; it < 5; it++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int c1 = 0, c2 = 0;
			
				for (int i1 = max(0, i - 5); i1 < min(i + 5, n); i1++) {
					for (int j1 = max(0, j - 5); j1 < min(j + 5, n); j1++) {
						if (A[i1][j1])
							c1++;
						else
							c2++;
					}
				}
				A[i][j] = (c1 > c2);
			}
		}
	}
	
	int cnt = 0, sq = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (A[i][j] && !used[i][j]) {
				
				s = 0;
				dfs(i, j);
				if (s <= 50)
					continue;
				
				if (A[i][j + 1] + A[i][j + 2] + A[i][j + 3] + A[i][j + 4] > 2)
					sq++;
			
				cnt++;
			}
		}
	}

	cout << cnt - sq << " " << sq;
	return 0;
}