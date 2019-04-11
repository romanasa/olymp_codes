#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 3007;
char R[dd][dd], D[dd][dd];

int dx[] = { 0, -1, -2 };
int dy[] = { 0,  1,  2 };
int n, m;

bool ok(int i, int j) { return i >= 0 && i < n && j >= 0 && j < m; }	

char tmm, used[dd][dd];
int pr[dd * dd * 2];
int cnt = 0;

bool dfs(int i, int j) {
	if (used[i][j] == tmm) return false;
	used[i][j] = tmm;
	
	int v = i * m + j;
	
	for (int gg = 0; gg < 3; gg++) {
		int ni = i + dx[gg];
		int nj = j + dy[gg];
		if (!ok(ni, nj) || !D[ni][nj]) continue;
		int to = ni * m + nj;
		
		if (pr[to] == -1) {
			pr[to] = v; pr[v] = to;
			cnt++;
			return true;
		}
	}
	
	for (int gg = 0; gg < 3; gg++) {
		int ni = i + dx[gg];
		int nj = j + dy[gg];
		if (!ok(ni, nj) || !D[ni][nj]) continue;
		int to = ni * m + nj;
		
		if (dfs(pr[to] / m, pr[to] % m)) {
			pr[to] = v; pr[v] = to;
			return true;
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	vector<string> A(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	
	int c = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (j + 2 < m && A[i][j] == 'R' && A[i][j + 1] == 'G' && A[i][j + 2] == 'W') R[i][j] = 1, c++;
			if (i + 2 < n && A[i][j] == 'R' && A[i + 1][j] == 'G' && A[i + 2][j] == 'W') D[i][j] = 1, c++;
		}
	}
	
	vector<int> q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) if (R[i][j]) {
			int t = 0;
			if (D[i][j]) t = 1;
			if (i > 0 && j + 1 < m && D[i - 1][j + 1]) t = 1;
			if (i > 1 && j + 2 < m && D[i - 2][j + 2]) t = 1; 
			if (t) q.push_back(i * m + j);
		}
	}
	
	fill(pr, pr + 2 * dd * dd, -1);
	
	for (int v : q) {
		int i = v / m, j = v % m;
		for (int gg = 0; gg < 3; gg++) {
			int ni = i + dx[gg];
			int nj = j + dy[gg];
    		if (!ok(ni, nj) || !D[ni][nj]) continue;
    		
    		int to = ni * m + nj;
    		
    		if (pr[to] == -1) {
    			pr[to] = v; pr[v] = to;
    			cnt++;
    			break;
    		}
    	}
	}
	
	for (int run = 1; run; ) {
		run = 0;
		tmm++;
		
		for (int v : q) if (pr[v] == -1 && dfs(v / m, v % m)) {
			run = 1;
		}
	}
	
	cout << c - cnt << "\n";	
	return 0;
}