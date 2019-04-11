#include <bits/stdc++.h>
#include "grader.h"

#define ll long long

using namespace std;

const int dd = (int)1e5 + 7;

struct pt {
	int x, y;
} T[1007];

int cT = 0;

struct vt {
	ll x, y;
	vt(pt a, pt b) {
		x = b.x - a.x;
		y = b.y - a.y;
	}
	ll operator % (vt b) {
		return x * b.y - y * b.x;
	}
};

int n;

void init() {}

bool check(pt A, pt B, pt C, pt M) {
	bool ok1 = true;
	
	if (vt(A, B) % vt(A, M) < 0)
		ok1 = false;
		
	if (vt(B, C) % vt(B, M) < 0)
		ok1 = false;
	
	if (vt(C, A) % vt(C, M) < 0)
		ok1 = false;
	
	return ok1;
}

void addPoints(int cnt, int *x, int *y) {
	for (int i = 0; i < cnt; i++) {
		T[cT++] = { x[i], y[i] };		
	}
}

void addTriangles(int cnt, int *x, int *y, int *r, int *ans) {
	for (int i = 0; i < cnt; i++) {
		ans[i] = 0;
		for (int j = 0; j < cT; j++) {
			if (check({ x[i], y[i] }, { x[i] + r[i], y[i] }, { x[i], y[i] + r[i] }, T[j]))
				ans[i]++;
		}	 
	}
}

/*
int main() {
	init();
	
	int x[3] = { 2, 4, 6 };
	int y[3] = { 2, 4, 6 };
	
	addPoints(3, x, y);
	
	int X[2] = { 1, 1 };
	int Y[2] = { 1, 1 };
	int R[2] = { 2, 6 };
	int ans[2];
	
	addTriangles(2, X, Y, R, ans);
	
	cout << ans[0] << " " << ans[1];
	return 0;
}*/
