#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

char A[234][456];

#define TASK "hexes"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, x, y, w, h;
	cin >> n >> x >> y >> w >> h;
	
	for (int i = 0; i < 2 * n + 1; i++)
		fill(A[i], A[i] + 4 * n, '.');
		
		
	for (int j = 0; j < n; j++) A[n][j] = '_';
	
	for (int t = 0; t < n; t++) A[n - t][n + t] = '/', A[2 * n - t][3 * n + t] = '/';
	for (int t = 0; t < n; t++) A[0][2 * n + t] = '_', A[2 * n][2 * n + t] = '_';
	for (int t = 0; t < n; t++) A[t + 1][3 * n + t] = '\\', A[n + 1 + t][n + t] = '\\';
		
	swap(x, y);
	
	y += 2 * n;
	x += 2 * n;
	
	
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << A[(i + x - 1) % (2 * n) + 1][(j + y) % (4 * n)];
		}
		cout << "\n";
	}
	

	return 0;
}