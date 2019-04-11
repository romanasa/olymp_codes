#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

char A[31][31];

int d[31][31][5];
int u[31][31][5];

int n, m;
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

bool ok(int i, int j) {
	return i >= 0 && i < n && j >= 0 && j < m;
}
	
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> A[i];
	
	int si = -1, sj = -1;
	int fi = -1, fj = -1;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (A[i][j] == 'B') si = i, sj = j;
			if (A[i][j] == '*') fi = i, fj = j;
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			d[i][j][0] = d[i][j][1] = d[i][j][2] = d[i][j][3] = (int)1e9;
		}
	}
	
	queue<pair<pair<int, int>, int> > q;
	d[si][sj][3] = 0;
	u[si][sj][3] = 1;
	
	q.push({ { si, sj }, 3 });
	
	while (q.size()) {
		int i = q.front().first.first, j = q.front().first.second, cnt = q.front().second;
		q.pop();
		
		u[i][j][cnt] = 0;
		
		for (int gg = 0; gg < 4; gg++) {
			int ni = i + dx[gg], nj = j + dy[gg];
			if (ok(ni, nj) && A[ni][nj] != 'W') {
				if (d[ni][nj][cnt] > d[i][j][cnt] + 1) {
					d[ni][nj][cnt] = d[i][j][cnt] + 1;
					if (!u[ni][nj][cnt]) {
						q.push({ { ni, nj }, cnt });
						u[ni][nj][cnt] = 1;
					}
				}
			}
			if (cnt && ok(ni, nj) && A[ni][nj] == 'W') {
				if (d[ni][nj][cnt - 1] > d[i][j][cnt] + 2) {
					d[ni][nj][cnt - 1] = d[i][j][cnt] + 2;
					if (!u[ni][nj][cnt - 1]) {
						q.push({ { ni, nj }, cnt - 1 });
						u[ni][nj][cnt - 1] = 1;
					}
				}
			}
		}
	}
	
	int ans = min({ d[fi][fj][0], d[fi][fj][1], d[fi][fj][2], d[fi][fj][3] });
	cout << (ans == (int)1e9 ? -1 : ans) << "\n";
	
	return 0;
}