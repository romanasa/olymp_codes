#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

#ifdef HOME
	const int dd = 7;
	const int maxC = 20;
	const int ADD = 6;
#else
	const int dd = 705;
	const int maxC = 6705;
	const int ADD = 3001;
#endif

int tmp[dd][maxC];
int A[maxC + 2 * dd][maxC];
short t[dd][dd];

void add(int j, int l, int r, int c) {
	j += ADD + dd;
	l += ADD;
	r += ADD;
	A[j][l] += c;
	A[j][r + 1] -= c;
}

int main() {
	int n, m;
	scanf("%d %d\n", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &t[i][j]);
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) if (t[i][j]) {
			int c = t[i][j] - 1;
			add(j + 1, i - c, i + c, -2);
		}
	}
	
	for (int j = ADD + dd; j < ADD + dd + m; j++) {
		int cur = 0;
		for (int i = 0; i < maxC; i++) {
			cur += A[j][i];
			if (0 <= i - ADD && i - ADD < n) tmp[i - ADD][j - dd] += cur;
		}
	}
	
	
	memset(A, 0, sizeof(A));
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) if (t[i][j]) {
			int c = t[i][j] - 1;
			add(i - (j - c), i, i + c, 1);
			add(i - (j + c + 2), i - c, i, 1);			
		}
	}
	
	for (int diff = 0; diff < maxC + 2 * dd; diff++) {
		int cur = 0;
		for (int i = 0; i < maxC; i++) {
			int j = (i - ADD) - (diff - ADD - dd);
			cur += A[diff][i];
			if (0 <= i - ADD && i - ADD < n) tmp[i - ADD][j + ADD] += cur;			
		}
	}
	
	memset(A, 0, sizeof(A));
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) if (t[i][j]) {
			int c = t[i][j] - 1;
			add(i - c + j, i - c, i - 1, 1);
			add(i + 1 + j + c + 1, i + 1, i + c, 1);
		}
	}
	
	for (int sum = 0; sum < maxC + 2 * dd; sum++) {
		int cur = 0;
		for (int i = 0; i < maxC; i++) {
			int j = (sum - ADD - dd) - (i - ADD);
			cur += A[sum][i];
			if (0 <= i - ADD && i - ADD < n) tmp[i - ADD][j + ADD] += cur;
		}
	}
	
	for (int i = 0; i < n; i++) {
		int cur = 0;
		for (int j = 0; j < maxC; j++) {
			cur += tmp[i][j];
			tmp[i][j] = cur;
		}
	}
	for (int i = 0; i < n; i++) {
		int cur = 0;
		for (int j = 0; j < maxC; j++) {
			cur += tmp[i][j];
			tmp[i][j] = cur;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cout << tmp[i][j + ADD] << " ";
		cout << "\n";
	}
	return 0;
}