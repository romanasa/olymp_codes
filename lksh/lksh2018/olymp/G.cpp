#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int G[31][31];
int deg1[31];

int H[31][31];
int deg2[31];

int n, m;

int P[31];
int used[31];

void go() {
	int ind = -1;
	for (int i = 0; i < n; i++) if (P[i] == -1) {
		if (ind == -1 || deg1[i] > deg1[ind]) ind = i;
	}
	if (ind == -1) {
		exit(0 * puts("YES"));
	}
	for (int v = 0; v < n; v++) if (!used[v] && deg2[v] == deg1[ind]) {
		int ok = 1;
		for (int j = 0; j < n; j++) if (P[j] != -1) {
			if (G[ind][j] != H[v][P[j]]) ok = 0;
		}
		if (ok) {
			P[ind] = v;
			used[v] = 1;
			go();
			P[ind] = -1;
			used[v] = 0;
		}
	}
}

void no() {
	exit(0 * puts("NO"));
}

int main() {


G[0][1] = 1;
G[0][2] = 1;
G[0][3] = 1;
G[0][9] = 1;
G[1][0] = 1;
G[1][2] = 1;
G[1][4] = 1;
G[1][5] = 1;
G[1][6] = 1;
G[2][0] = 1;
G[2][1] = 1;
G[2][6] = 1;
G[2][7] = 1;
G[2][8] = 1;
G[2][9] = 1;
G[3][0] = 1;
G[3][4] = 1;
G[3][9] = 1;
G[3][10] = 1;
G[4][1] = 1;
G[4][3] = 1;
G[4][5] = 1;
G[4][11] = 1;
G[5][1] = 1;
G[5][4] = 1;
G[5][6] = 1;
G[5][12] = 1;
G[6][1] = 1;
G[6][2] = 1;
G[6][5] = 1;
G[6][7] = 1;
G[6][13] = 1;
G[7][2] = 1;
G[7][6] = 1;
G[7][8] = 1;
G[7][14] = 1;
G[8][2] = 1;
G[8][7] = 1;
G[8][9] = 1;
G[8][15] = 1;
G[9][0] = 1;
G[9][2] = 1;
G[9][3] = 1;
G[9][8] = 1;
G[9][16] = 1;
G[10][3] = 1;
G[11][4] = 1;
G[12][5] = 1;
G[13][6] = 1;
G[14][7] = 1;
G[15][8] = 1;
G[16][9] = 1;


	cin >> n >> m;
	
	if (n != 17 || m != 26) no();
	fill(P, P + 31, -1);
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		H[a - 1][b - 1] = H[b - 1][a - 1] = 1;
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) deg1[i] += G[i][j];
		for (int j = 0; j < n; j++) deg2[i] += H[i][j];
	}
	
	go();
	no();
	return 0;
}