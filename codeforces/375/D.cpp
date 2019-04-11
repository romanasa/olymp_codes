#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

int n, m, k;

bool ok(int i, int j) {
	return i >= 0 && i < n && j >= 0 && j < m;
}

bool ocean(int i, int j) {
	return i == 0 || j == 0 || i == n - 1 || j == m - 1;
}

int tp[57][57];
int bad[3007], sq[3007], J[3007];
string A[57];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void mark(int i, int j, int c) {
	if (ocean(i, j))
		bad[c] = 1;
	sq[c]++;
	tp[i][j] = c;
	for (int gg = 0; gg < 4; gg++) {
		int ni = i + dx[gg], nj = j + dy[gg];		
		if (ok(ni, nj) && A[ni][nj] == '.' && tp[ni][nj] == 0)
			mark(ni, nj, c);
	}
}

int main() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
		cin >> A[i];
		
	int c = 1;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (A[i][j] == '.' && tp[i][j] == 0)
				mark(i, j, c++);
		}
	}
	
	int t = 0;
	vector<pair<int, int> > T;
	for (int i = 1; i < c; i++) {
		if (!bad[i])
			T.push_back({ sq[i], i });
		else
			t++;
	}
	
	sort(T.begin(), T.end());
	for (int i = 0; i < c; i++) {
		if (c - 1 - t - i > k) {
			J[T[i].second] = 1;
		} else {
			break;
		}
	}
	
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			if (J[tp[i][j]])
				A[i][j] = '*', ans++;
	}
	cout << ans << "\n";
	for (int i = 0; i < n; i++) {
		cout << A[i] << "\n";
	}
	return 0;
}