#include "grader.h"

#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int dd = (int)2e6 + 7;
const int inf = (int)1e9 + 7;


int L[4 * dd], R[4 * dd];

void calc(int v, int l, int r) {
	L[v] = min(L[v], l);
	L[v] = max(L[v], r);
	
	R[v] = min(R[v], l);
	R[v] = max(R[v], r);
}

void updMin(int v, int tl, int tr, int l, int r, int t) {
	if (l > r)
		return;
		
	if (l == tl && tr == r) {
		L[v] = min(L[v], t);
		R[v] = min(R[v], t);
	} else {
		int tm = (tl + tr) / 2;
		
		calc(v * 2, L[v], R[v]);
		calc(v * 2 + 1, L[v], R[v]);
		
		L[v] = inf, R[v] = 0;
		
		updMin(v * 2, tl, tm, l, min(r, tm), t);
		updMin(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, t);	
	}
}

void updMax(int v, int tl, int tr, int l, int r, int t) {
	if (l > r)
		return;
		
	if (l == tl && tr == r) {
		L[v] = max(L[v], t);
		R[v] = max(R[v], t);
	} else {
		int tm = (tl + tr) / 2;
		
		calc(v * 2, L[v], R[v]);
		calc(v * 2 + 1, L[v], R[v]);
		
		L[v] = inf, R[v] = 0;
		
		updMax(v * 2, tl, tm, l, min(r, tm), t);
		updMax(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, t);	
	}
}

int get(int v, int tl, int tr, int pos) {
	if (tl == tr)
		return min(L[v], R[v]);
		
	calc(v * 2, L[v], R[v]);
	calc(v * 2 + 1, L[v], R[v]);
	
	int tm = (tl + tr) / 2;
	if (pos <= tm)
		return get(v * 2, tl, tm, pos);
	else
		return get(v * 2 + 1, tm + 1, tr, pos);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]) {
	for (int i = 0; i < k; i++) {
		if (op[i] == 1) {
			updMax(1, 0, n - 1, left[i], right[i], height[i]);			
		} else {
			updMin(1, 0, n - 1, left[i], right[i], height[i]);
		}
	}
	for (int i = 0; i < n; i++)
		finalHeight[i] = get(1, 0, n - 1, i);
}
