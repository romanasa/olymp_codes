#ifdef HOME
	#include "quality.h"
#else
	#include "grader.h"
#endif

int P[3001][3001];

inline int get(int i1, int j1, int i2, int j2) {
	return P[i2][j2] - (i1 ? P[i1 - 1][j2] : 0) - (j1 ? P[i2][j1 - 1] : 0) + (i1 && j1 ? P[i1 - 1][j1 - 1] : 0);
}

int rectangle(int R, int C, int H, int W, int Q[3001][3001]) {


	int l = 0, r = R * C + 1;
	
	while (r - l > 1) {
		int m = (l + r) / 2;
		
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				P[i][j] = (i ? P[i - 1][j] : 0) + (j ? P[i][j - 1] : 0) - (i && j ? P[i - 1][j - 1] : 0) + (Q[i][j] <= m);
			}
		}
		
		int ok = 0;
		for (int i = 0; i + H - 1 < R; i++) {
			for (int j = 0; j + W - 1 < C; j++) {
				if (get(i, j, i + H - 1, j + W - 1) >= (H * W + 1) / 2)
					ok = 1;
			}
		}
		
		if (ok) {
			r = m;
		} else {
			l = m;
		}
	}

	return r;
}
