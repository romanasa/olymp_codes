#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int dd = (int)2e4 + 1;

int A1[2001], A2[2001];
int B1[2001], B2[2001];
int x[dd], y[dd];

int main() {
	int n;
	scanf("%d", &n);
	
	x[0] = 1000, y[0] = 1000;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &x[i], &y[i]);
		x[i] += 1000;
		y[i] += 1000;	
	}
	
	for (int j = 0; j < 2001; j++) {
		A1[j] = B1[j] = A2[j] = B2[j] = (int)1e9;
	}

	for (int j = 0; j < 2001; j++) {
		A1[j] = abs(j - 1000);
		B1[j] = abs(j - 1000);
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2001; j++) {
			A2[j] = min(A1[j] + abs(x[i + 1] - x[i]), B1[x[i + 1]] + abs(j - y[i]));
			B2[j] = min(B1[j] + abs(y[i + 1] - y[i]), A1[y[i + 1]] + abs(j - x[i]));
		}
		for (int j = 0; j < 2001; j++) {
			A1[j] = A2[j], A2[j] = (int)1e9;
			B1[j] = B2[j], B2[j] = (int)1e9;
		}
	}
	
	int ans = (int)1e9 + 1;
	for (int j = 0; j < 2001; j++)
		ans = min(ans, min(A1[j], B1[j]));
	printf("%d\n", ans);
	return 0;
}