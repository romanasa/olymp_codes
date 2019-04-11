#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const int dd = (int)1001;

struct ev {
	int val;
	short x, y;
	bool operator < (ev b) const {
		return val < b.val;
	}
};

int A[dd][dd], P[dd][dd];
ev B[dd][dd], C[dd][dd];
ev D[dd][dd];

inline int get(int x1, int y1, int x2, int y2) {
	return P[x2][y2] - (x1 ? P[x1 - 1][y2] : 0) - (y1 ? P[x2][y1 - 1] : 0) + (x1 && y1 ? P[x1 - 1][y1 - 1] : 0);
}

int main() {
	int n, m, a, b, c, d;
	cin >> m >> n >> b >> a >> d >> c;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &A[i][j]);
			P[i][j] = (i ? P[i - 1][j] : 0) + (j ? P[i][j - 1] : 0) - (i && j ? P[i - 1][j - 1] : 0) + A[i][j];
		}
	}
	
	for (int i = 0; i + c - 1 < n; i++) {
		for (int j = 0; j + d - 1 < m; j++) {
			B[i][j] = { get(i, j, i + c - 1, j + d - 1), i, j };
		}
	}
	
	
	int len = b - d - 1;
	
	for (int i = 0; i < n; i++) {
		multiset<ev> S;
		
		for (int j = m - d; j >= 0; j--) {
			S.insert(B[i][j]);
			
			if (j + len < m - d + 1)
				S.erase(S.find(B[i][j + len]));
				
			C[i][j] = *S.begin();
		};
	}	
	
	len = a - c - 1;
	for (int j = 0; j < m; j++) {
		multiset<ev> S;
		
		for (int i = n - c; i >= 0; i--) {
			S.insert(C[i][j]);
			
			if (i + len < n - c + 1)
				S.erase(S.find(C[i + len][j]));
				
			D[i][j] = *S.begin();
		}
	}
	/*
	err("B:");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			err("%d%c", B[i][j].val, " \n"[j == m - 1]);
	
	err("\n\nC:");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			err("%d%c", C[i][j].val, " \n"[j == m - 1]);
	
	err("\n\nD:");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			err("%d%c", D[i][j].val, " \n"[j == m - 1]);
	*/
	int ans = 0;
	for (int i = 0; i + a - 1 < n; i++) {
		for (int j = 0; j + b - 1 < m; j++) {
			int cur = get(i, j, i + a - 1, j + b - 1) - D[i + 1][j + 1].val;
			ans = max(ans, cur);
		}
	}
	
	for (int i = 0; i + a - 1 < n; i++) {
		for (int j = 0; j + b - 1 < m; j++) {
			int cur = get(i, j, i + a - 1, j + b - 1) - D[i + 1][j + 1].val;
			if (ans == cur) {
				printf("%d %d\n%d %d\n", j + 1, i + 1, D[i + 1][j + 1].y + 1, D[i + 1][j + 1].x + 1);
				return 0;
			}
		}
	}
	
	return 0;
}