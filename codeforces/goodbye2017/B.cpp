#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

string A[57];

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

int n, m;

bool ok(int i, int j) { return i >= 0 && i < n && j >= 0 && j < m && A[i][j] != '#'; }	

int main() {
	cin >> n >> m;
	
	for (int i = 0; i < n; i++) cin >> A[i];
	
	int si = -1, sj = -1;
	int fi = -1, fj = -1;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (A[i][j] == 'S') si = i, sj = j;
			if (A[i][j] == 'E') fi = i, fj = j;
		}
	}
	
	string s;
	cin >> s;
	
	vector<int> p = { 0, 1, 2, 3 };
	
	int ans = 0;
	do {
		int i = si, j = sj;
		int t = 0;
		
		for (char c : s) {
			int gg = p[c - '0'];
			i += dx[gg];
			j += dy[gg];
			if (!ok(i, j)) break;
			if (i == fi && j == fj) t = 1;
		}
		ans += t;
		
	} while (next_permutation(p.begin(), p.end()));
	
	
	cout << ans;
	
	return 0;
}