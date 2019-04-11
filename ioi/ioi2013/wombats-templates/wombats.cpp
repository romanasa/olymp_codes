#include <bits/stdc++.h>
#include "grader.h"
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)5001;
const int sz = 15;

int R, C;

int H[dd][201];
int V[dd][201];

struct node {
	int **A;
	void resize() {
		A = new int*[C];
		for (int i = 0; i < C; i++) A[i] = new int[C];
	}
	int* operator [](int a) {
		return A[a];
	}
} T[10024];

int opt[201][201];

void merge(node &cur, node &A, node &B) {
	for (int i = 0; i < C; i++) {
		opt[i][C] = C - 1;
		for (int j = C - 1; j >= 0; j--) {
		
			int l = (i ? opt[i - 1][j] : 0);
			int r = opt[i][j + 1];
			int tmp;
		
			cur[i][j] = (int)1e9 + 1;
			for (int k = l; k <= r; k++) {
				if (cur[i][j] > (tmp = (A[i][k] + B[k][j]))) {
					cur[i][j] = tmp;
					opt[i][j] = k;
				}
			}		
		}
	}
}

void upd(int* A, int r) {
	for (int i = 1; i < C; i++)
		A[i] = min(A[i], A[i - 1] + H[r][i - 1]);
	for (int i = C - 2; i >= 0; i--)
		A[i] = min(A[i], A[i + 1] + H[r][i]);
}

void calc(int v, int L, int R) {
	for (int i = 0; i < C; i++) {
		for (int j = 0; j < C; j++) {
			T[v][i][j] = (i == j ? 0 : (int)1e9 + 1);
		}
		for (int r = L; r < R; r++) {
			upd(T[v][i], r);	
			for (int j = 0; j < C; j++) T[v][i][j] += V[r][j];
		}
	}
}

void upd(int v, int tl, int tr, int pos) {
	if (tl + 1 >= R) return;
	
	if (pos == -1) T[v].resize();
	
	if (tr - tl == sz) {
		calc(v, tl, min(tr, R - 1));
	} else {
		int tm = (tl + tr) / 2;
		
		if (pos == -1 || pos < tm)
			upd(v * 2, tl, tm, pos);
		if (pos == -1 || pos >= tm)
			upd(v * 2 + 1, tm, tr, pos);

		if (tm + 1 < R) {
			merge(T[v], T[v * 2], T[v * 2 + 1]);
		} else {
			T[v] = T[v * 2];
		}
	}
}

void init(int R, int C, int HH[5000][200], int VV[5000][200]) {
	::R = R, ::C = C;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			H[i][j] = HH[i][j], V[i][j] = VV[i][j];
	upd(1, 0, 512 * sz, -1);
}

void changeH(int P, int Q, int W) {
    H[P][Q] = W;
    upd(1, 0, 512 * sz, P);
}

void changeV(int P, int Q, int W) {
    V[P][Q] = W;
    upd(1, 0, 512 * sz, P);
}

int escape(int V1, int V2) {
	upd(T[1][V1], R - 1);
	return T[1][V1][V2];
}
