#include <bits/stdc++.h>
#define ll long long

#include "grader.h"

using namespace std;

const int dd = (int)1e5 + 7;
int n;
ll G[dd], P[dd];

ll get(int l, int r) {
	int pos = (l + r) / 2;
	return (pos - l) * G[pos] - (P[pos] - P[l]) + (P[r + 1] - P[pos + 1]) - (r - pos) * G[pos];
}

bool check(int M, ll B) {
	for (int i = 0; i + M - 1 < n; i++) {
		if (get(i, i + M - 1) <= B)
			return true;
	}
	return false;
}

int besthub(int R, int L, int A[], ll B) {
	n = R;
	copy(A, A + n, G);
	
	for (int i = 0; i < n; i++)
		P[i + 1] = P[i] + G[i];
		
	int l = 0, r = n + 1;
	while (r - l > 1) {
		int m = (l + r) / 2;
		if (check(m, B))
			l = m;
		else
			r = m;
	}

	return l;
}
