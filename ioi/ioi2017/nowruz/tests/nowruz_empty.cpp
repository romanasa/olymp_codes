#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int maxN = 1234;

char A[maxN][maxN];
int used[maxN][maxN];
int n, m, k;

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

bool ok(int i, int j) { return i >= 0 && i < n && j >= 0 && j < m; }

int main(int argc, char* argv[]) {
	scanf("%d %d %d", &n, &m, &k);
	/*
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) putchar(A[i][j]);
		putchar('\n');
	}*/
	
	used[0][0] = 1;
	int need = 1;
	while (need) {
		need = 0;
		for (int i = 0; i < n && !need; i++) {
			for (int j = 0; j < m && !need; j++) if (!used[i][j]) {
				int c = 0;	
				for (int gg = 0; gg < 4; gg++) {
					int ni = i + dx[gg], nj = j + dy[gg];
					if (ok(ni, nj) && used[ni][nj]) c++;
				}
				if (c == 1) { used[i][j] = 1; need = 1; }
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) putchar(!used[i][j] ? 'X' : '.');
		putchar('\n');
	}
	
	//err("score = %.2f\n", 10.0 * ans / k);
	return 0;
}
