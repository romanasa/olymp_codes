#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

char A[51][21];

int G[31][31], out[31];
int U[31];

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

int used[51][21];
int n, m = 20;

bool ok(int i, int j) { return i >= 0 && i < n && j >= 0 && j < m; }

void dfs(int i, int j) {
	for (int t = i + 1; t < n; t++) {
		if (A[t][j] != '.' && A[i][j] != A[t][j]) {
			//err("add from %c to %c\n", A[i][j], A[t][j]);
			G[A[i][j] - 'A'][A[t][j] - 'A']++;
			out[A[i][j] - 'A']++;
		}
	}
	used[i][j] = 1;
	for (int gg = 0; gg < 4; gg++) {
		int ni = i + dx[gg], nj = j + dy[gg];
		if (ok(ni, nj) && !used[ni][nj] && A[ni][nj] == A[i][j]) {
			dfs(ni, nj);
		}
	}
}

int main() {
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf("%s", A[i]);
	}
		
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (A[i][j] != '.' && !U[A[i][j] - 'A']) {
				U[A[i][j] - 'A'] = 1;
				//err("dfs (%d, %d)\n", i, j);
				dfs(i, j);
			}
		}
	}
	
	while (1) {
		int ind = -1;
		for (int i = 0; i < 26; i++) {
			if (U[i] && out[i] == 0) {
				ind = i;
				break;
			}
		}
		if (ind == -1) break;
		
		U[ind] = 0;
		for (int i = 0; i < 26; i++) out[i] -= G[i][ind];

		printf("%c", (char)(ind + 'A'));
	}
	puts("");
	
	return 0;
}