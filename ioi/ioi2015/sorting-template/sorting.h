#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int dd = (int)2e5 + 7;

struct SegmentTreeMin {
	pair<int, int> T[4 * dd];
	
	void build(int v, int tl, int tr, vector<int> &A) {
		if (tl == tr)
			T[v] = { A[tl], tl };
		else {
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm, A);
			build(v * 2 + 1, tm + 1, tr, A);
			
			T[v] = min(T[v * 2], T[v * 2 + 1]);
		}
	}
	
	void upd(int v, int tl, int tr, int pos, int val) {
		if (tl == tr) {
			T[v] = { val, tl };
		} else {
			int tm = (tl + tr) / 2;
			if (pos <= tm)
				upd(v * 2, tl, tm, pos, val);
			else
				upd(v * 2 + 1, tm + 1, tr, pos, val);
				
			T[v] = min(T[v * 2], T[v * 2 + 1]);
		}
	}
	
	pair<int, int> get(int v, int tl, int tr, int l, int r) {
		if (l == tl && r == tr)
			return T[v];
		int tm = (tl + tr) / 2;
		if (r <= tm)
			return get(v * 2, tl, tm, l, r);
		if (l > tm)
			return get(v * 2 + 1, tm + 1, tr, l ,r);
		return min(get(v * 2, tl, tm, l, tm), get(v * 2 + 1, tm + 1, tr, tm + 1, r));
	}
} F;

int get(vector<int> T) {
	int cur = 0;
	int n = (int)T.size();
	
	F.build(1, 0, n - 1, T);
		
	for (int i = 0; i < n; i++) {
		int ind = F.get(1, 0, n - 1, i, n - 1).second;
				
		if (i != ind) {
			F.upd(1, 0, n - 1, i, T[ind]);
			F.upd(1, 0, n - 1, ind, T[i]);
			swap(T[i], T[ind]), cur++;
		}
	}
	return cur;
}

void rec(vector<int> T, int* P, int* Q) {
	int n = (int)T.size();
	int iP = 0;
	
	F.build(1, 0, n - 1, T);
	
	for (int i = 0; i < n; i++) {
		int ind = F.get(1, 0, n - 1, i, n - 1).second;
	
		if (i != ind) {
			P[iP] = T[i], Q[iP] = T[ind];
			iP++;
			
			F.upd(1, 0, n - 1, i, T[ind]);
			F.upd(1, 0, n - 1, ind, T[i]);
			swap(T[i], T[ind]);
		}
	}
}

int findSwapPairs(int n, int S[], int M, int X[], int Y[], int P[], int Q[]) {
	
	int l = -1, r = n;
	while (r - l > 1) {
		int m = (l + r) / 2;
		
		vector<int> T(n);
		for (int i = 0; i < n; i++)
			T[i] = S[i];

			
		for (int i = 0; i < m; i++)
			swap(T[X[i]], T[Y[i]]);

			
		if (get(T) <= m)
			r = m;
		else
			l = m;
	}
	
	for (int i = 0; i < r; i++)
		P[i] = Q[i] = 0;
	
	vector<int> T(n), J(n);
	for (int i = 0; i < n; i++)
		T[i] = S[i];
			
	for (int i = 0; i < r; i++) {
		swap(T[X[i]], T[Y[i]]);
	}
		
	rec(T, P, Q);
		
	for (int i = 0; i < n; i++) 
		T[i] = S[i];
	
	for (int i = 0; i < n; i++)
		J[T[i]] = i;
	
	for (int i = 0; i < r; i++) {		
		swap(J[T[X[i]]], J[T[Y[i]]]);
		swap(T[X[i]], T[Y[i]]);
		
		P[i] = J[P[i]], Q[i] = J[Q[i]];
		
		swap(J[T[P[i]]], J[T[Q[i]]]);
		swap(T[P[i]], T[Q[i]]);
	}
	return r;
}
	

