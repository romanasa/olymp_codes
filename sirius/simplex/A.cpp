#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 1007;

long double A[dd][dd];
long double AN[dd][dd];

long double X[dd], Y[dd], res[dd];

#define TASK "simplex"

int sgn(long double x) {
	return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n + 1; j++) cin >> A[i][j];
	}
	
	for (int i = 1; i <= n; i++) {
		cin >> A[m + 1][i];
		A[m + 1][i] *= -1;
	}
	
	for (int i = 1; i <= n; i++) A[0][i] = i;
	for (int i = 1; i <= m; i++) A[i][0] = 0;
	
	int it = 0;
	
	while (1) {
	
		int ind = min_element(A[m + 1] + 1, A[m + 1] + n + 2) - A[m + 1];
		
		if (A[m + 1][ind] >= 0) break;
		
		if (++it > 5) break;
		
		for (int i = 0; i <= m + 1; i++) {
			for (int j = 0; j <= m + 1; j++) {
				printf("%.3f%c", (double)A[i][j], " \n"[j == m + 1]);
			}
		}
		
		int t = 1;
		for (int i = 1; i <= m; i++) {
			if (A[i][n + 1] / A[i][ind] < A[t][n + 1] / A[t][ind]) t = i;
		}	
		
		err("%.3f / %.3f\n", (double)A[t][n + 1], (double)A[t][ind]);
		
		
		//if (sgn(A[t][n + 1]) != sgn(A[t][ind])) return 0 * puts("Unbounded");
		
		AN[t][ind] = 1 / A[t][ind];
		
		for (int i = 1; i <= m + 1; i++) if (i != t) {
			AN[i][ind] = A[i][ind] / A[t][ind] * (-1);
		}
		
		for (int i = 1; i <= n + 1; i++) if (i != ind) {
			AN[t][i] = A[t][i] / A[t][ind];
		}
		
		for (int i = 1; i <= n; i++) AN[0][i] = A[0][i];
		for (int i = 1; i <= m; i++) AN[i][0] = A[i][0];
		
		swap(AN[0][ind], AN[t][0]);
		
		for (int i = 1; i <= m + 1; i++) {
			for (int j = 1; j <= n + 1; j++) {
				if (i == t || j == ind) continue;
				AN[i][j] = A[i][j] - (A[i][ind] * A[t][j]) / A[t][ind];
			}
		}
		
		for (int i = 0; i <= m + 1; i++) {
			for (int j = 0; j <= n + 1; j++) {
				A[i][j] = AN[i][j];
			}
		}
	}

	puts("Bounded");
	
	for (int i = 1; i <= m; i++) {
		if (A[i][0] > 0.5) {
			res[(int)(A[i][0] + 0.5)] = A[i][n + 1];
		}
	}
	for (int i = 1; i <= n; i++) printf("%.10f ", (double)res[i]);
	
	return 0;
}