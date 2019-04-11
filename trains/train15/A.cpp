#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 1030;

int dp[3][11][dd][dd];
int u[3][11][dd][dd];
int n, m;
char A[dd][dd];

int calc(int x, int y) { 
	if (x == y) return 3;
	if (x % 2 == y % 2) return 1;
	return 0;
}

int calc1(int x, int y, int sz) {
	int cur = 0;
	for (int i = 0; i < sz; i++) cur += calc(A[x][y + i] - '0', A[x - 1][y + i] - '0');
	return cur;
}

int calc2(int x, int y, int sz) {
	int cur = 0;
	for (int i = 0; i < sz; i++) cur += calc(A[x + i][y] - '0', A[x + i][y - 1] - '0');
	return cur;
}

int F(int x, int y, int n, int d) {
	if (u[d + 1][n][x][y]) return dp[d + 1][n][x][y];
	int m = n + d;
	if (n == 0 && m == 0) return 0;
	int a = (1 << n);
	int b = (1 << m);
	
	int cur = -(int)1e9;
	
	if (a >= 2 && a >= b) {
		int score = calc1(x + a / 2, y, b);
		int t = min(F(x, y, n - 1, d + 1), F(x + a / 2, y, n - 1, d + 1));
		cur = max(cur, score - t); 
	}
	if (b >= 2 && b >= a) {
		int score = calc2(x, y + b / 2, a);
		int t = min(F(x, y, n, d - 1), F(x, y + b / 2, n, d - 1));
		cur = max(cur, score - t);
	}
	u[d + 1][n][x][y] = 1;
	return dp[d + 1][n][x][y] = cur;
}

int main() {
	scanf("%d %d", &n, &m);
	int pn = n, pm = m;
	n = 1 << n;
	m = 1 << m;
	
	for (int i = 0; i < n; i++) scanf("%s", A[i]);
	printf("%d\n", F(0, 0, pn, pm - pn));
	
	return 0;
}