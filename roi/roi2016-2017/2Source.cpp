#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <queue>
#include <string>
#include <cassert>
#include <bitset>

using namespace std;

int solve();

typedef long long ll;

#define TASK "order"

int main() {
#ifdef ROII
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

const int dd = (int)1e6 + 1;
const int LOG = 30;
int A[dd];
int P[LOG + 1];

bitset<30> Q;

struct node {
	int l, r;
	int C0, C1;
	void clear() { C0 = (1 << LOG) - 1, C1 = (1 << LOG) - 1; }
};

void merge(node A, node B, node &C) {
	C.clear();
	C.l = A.l, C.r = B.r;

	C.C0 = A.C0 & B.C0;
	C.C1 = A.C1 & B.C1;

	if (A.r == B.l) return;

	int l = 0, r = 30;
	while (r - l > 1) {
		int m = (l + r) / 2;

		if ((A.r & P[m]) == (B.l & P[m]))
			l = m;
		else
			r = m;
	}

	int i = l;

	int a = (A.r >> (LOG - i - 1)) & 1;
	int b = (B.l >> (LOG - i - 1)) & 1;

	if (a < b) {
		int t = ((A.C0 >> i) & 1) & ((B.C0 >> i) & 1);
		if (((C.C0 >> i) & 1) ^ t)
			C.C0 ^= (1 << i);
		if (C.C1 & (1 << i)) C.C1 ^= 1 << i;
	} else {
		if (C.C0 & (1 << i)) C.C0 ^= 1 << i;
		int t = ((A.C1 >> i) & 1) & ((B.C1 >> i) & 1);
		if (((C.C1 >> i) & 1) ^ t)
			C.C1 ^= (1 << i);
	}
	
}

node T[4 * dd];

void build(int v, int tl, int tr) {
	if (tl == tr) {
		T[v].l = T[v].r = A[tl];
		T[v].clear();
	} else {
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm + 1, tr);
		merge(T[v * 2], T[v * 2 + 1], T[v]);
	}
}

void upd(int v, int tl, int tr, int pos, int val) {
	if (tl == tr) {
		T[v].l = T[v].r = val;
		T[v].clear();
	} else {
		int tm = (tl + tr) / 2;
		if (pos <= tm) upd(v * 2, tl, tm, pos, val);
		else upd(v * 2 + 1, tm + 1, tr, pos, val);
		merge(T[v * 2], T[v * 2 + 1], T[v]);
	}
}

int get() {
	int ans = 0;
	for (int i = 0; i < LOG; i++) {
		if (((T[1].C0 >> i) & 1) == 0) {
			if ((T[1].C1 >> i) & 1) ans += (1 << (LOG - i - 1));
			else return -1;
		}
	}
	return ans;
}

int solve() {
	for (int i = 1; i <= LOG; i++) {
		P[i] = P[i - 1] + (1 << (LOG - i));
	}

	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}

	build(1, 0, n - 1);
	printf("%d\n", get());

	int q;
	scanf("%d", &q);
	while (q--) {
		int a, b;
		scanf("%d %d", &a, &b);
		upd(1, 0, n - 1, a - 1, b);
		printf("%d\n", get());
	}

	return 0;
}