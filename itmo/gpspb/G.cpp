#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int d[507][507];

#define TASK "mole"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, m;
	cin >> n >> m;
	
	vector<string> A(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	
	queue<pair<int, int> > q;
	for (int i = 0; i < m; i++) if (A[0][i] == '.') {
		d[0][i] = 1, q.push({ 0, i });
	}
	
	while (q.size()) {
		int i = q.front().first, j = q.front().second;
		q.pop();
		
		if (A[i + 1][j] == '.') {
			if (!d[i + 1][j]) {
				d[i + 1][j] = 1;
				q.push({ i + 1, j });
			}
		} else {
			for (int dy = -1; dy <= 1; dy += 2) {
				if (j + dy >= 0 && j + dy < m && A[i][j + dy] == '.') {
					if (!d[i][j + dy]) d[i][j + dy] = 1, q.push({ i, j + dy });
				}
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) if (A[i][j] == '.' && !d[i][j]) {
			cout << "Yes\n";
			A[i][j] = 'X';
			for (int i = 0; i < n; i++) cout << A[i] << "\n";;
			return 0;
		}
	}
	cout << "No\n";

	return 0;
}