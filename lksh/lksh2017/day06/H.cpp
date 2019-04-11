#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<string> A;

int U[2345][2345];
int Q[2345][2345];
pair<int, int> C[2345][2345];

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };
int cnt, num;


int n, m;
bool ok(int i, int j) {
	return i >= 0 && i < n && j >= 0 && j < m;
}

void dfs(int i, int j) {
	cnt++;
	U[i][j] = 1;
	for (int gg = 0; gg < 4; gg++) {
		int ni = i + dx[gg], nj = j + dy[gg];
		if (ok(ni, nj) && A[ni][nj] == '#' && !U[ni][nj])
			dfs(ni, nj);
	}
}

void mark(int i, int j) {
	C[i][j] = { cnt, num };
	Q[i][j] = 1;
	for (int gg = 0; gg < 4; gg++) {
		int ni = i + dx[gg], nj = j + dy[gg];
		if (ok(ni, nj) && A[ni][nj] == '#' && !Q[ni][nj])
			mark(ni, nj);
	}
}

int main() {
#ifndef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
	cin >> m >> n;
	
	A.resize(n);
	for (int i = 0; i < n; i++) cin >> A[i];

	int ans = -1, ii = -1, jj = -1;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (A[i][j] == '#' && !U[i][j]) {
				cnt = 0, num++;
				dfs(i, j);
				mark(i, j);
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (A[i][j] == '.') {
				set<pair<int, int> > S;
				for (int gg = 0; gg < 4; gg++) {
					int ni = i + dx[gg], nj = j + dy[gg];
					if (ok(ni, nj) && A[ni][nj] == '#') S.insert(C[ni][nj]);
				}
				
				int cur = 0;
				for (auto c : S) cur += c.first;
				
				if (ans < cur) {
					ans = cur, ii = i, jj = j;
				}
			}
		}
	}
	cout << jj + 1 << " " << ii + 1 << "\n";	
	return 0;
}