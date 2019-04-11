#include <bits/stdc++.h>
#define ll long long
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

#include "grader.h"

using namespace std;

int ok;

double f(int xx) {
	double p, q;
	
	double x = xx;
	question(1, 0, x, &p, &q);
	double a, b;
	question(1, 0, x + 1e-5, &a, &b);
	
	if (a - p == 0) {
		x -= 0.1;
		question(1, 0, x, &p, &q);
		question(1, 0, x + 1e-5, &a, &b);
	}
	return a - p;
}

double f2(int xx) {

	double x = xx;

	double p, q;
	question(0, 1, x, &p, &q);
	double a, b;
	question(0, 1, x + 1e-5, &a, &b);
	
	if (a - p == 0) {
		x -= 0.1;
		
		question(0, 1, x, &p, &q);
		question(0, 1, x + 1e-5, &a, &b);
	}
	
	return a - p;
}

double ask(int x1, int y1, int x2, int y2, int x3, int y3) {
	double p, q;
	int a = y2 - y1;
	int b = x1 - x2;
	if (a == 0 && b == 0) return 0;
	int t = __gcd(a, b);
	a /= t;
	b /= t;
	int c = a * x1 + b * y1;
	
	if (1ll * a * a + 1ll * b * b > (int)1e6) {
		double aa = a / 2.0, bb = b / 2.0, cc = c / 2.0;
		question(aa, bb, cc, &p, &q);
		return (aa * x3 + bb * y3 < cc && p == 1) || (aa * x3 + bb * y3 > cc && q == 1);	
	}
	question(a, b, c, &p, &q);
	return (a * x3 + b * y3 < c && p == 1) || (a * x3 + b * y3 > c && q == 1);
}

pair<int, int> Q[5];

double dist(int x1, int y1, int x2, int y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void check(int x1, int y1, int x2, int y2, int x3, int y3) {
	if (x1 == x2 && x1 == x3) return;
	if (y1 == y2 && y1 == y3) return;
	if (ask(x1, y1, x2, y2, x3, y3) && ask(x2, y2, x3, y3, x1, y1) && ask(x3, y3, x1, y1, x2, y2))
		Q[0] = { x1, y1 }, Q[1] = { x2, y2 }, Q[2] = { x3, y3 }, ok = 1;
}

void solution(int group_id, int **answer) {
	//freopen("02", "w", stderr);
	int lx, rx;
	int ly, ry;
	
	{
		
		int l = -1001, r = 1001;
	
		while (r - l > 1) {
			int m = (l + r) / 2;
			double a, b;
			question(1, 0, m, &a, &b);
			
			//err("ask %d * x + %d * y = %d, (%.3f, %.3f)\n", 1, 0, m, a, b);
			if (a == 0)
				l = m;
			else
				r = m;
		}
		lx = l;
	}
	
	{
		
		int l = -1001, r = 1001;
	
		while (r - l > 1) {
			int m = (l + r) / 2;
			double a, b;
			question(0, 1, m, &a, &b);
			
			//err("ask %d * x + %d * y = %d, (%.3f, %.3f)\n", 1, 0, m, a, b);
			if (a == 0)
				l = m;
			else
				r = m;
		}
		ly = l;
	}
	
	{
		int l = -1001, r = 1001;
		
		while (r - l > 1) {
			int m = (l + r) / 2;
			double a, b;
			question(1, 0, m, &a, &b);
			if (b == 0)
				r = m;
			else
				l = m;
		}
		rx = r;
	}
	
	{
		int l = -1001, r = 1001;
		
		while (r - l > 1) {
			int m = (l + r) / 2;
			double a, b;
			question(0, 1, m, &a, &b);
			if (b == 0)
				r = m;
			else
				l = m;
		}
		ry = r;
	}
	
	int mx, my;
	
	{
		int l = lx, r = rx;
		while (r - l > 3) {
			int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
			if (f(m1) < f(m2))
				l = m1;
			else
				r = m2; 
		}
		mx = l;
		//err("l = %d, r = %d\n", l, r);
		for (int m = l; m <= r; m++) {
			if (f(m) > f(mx)) 
				mx = m;
			//err("F(%d) = %.10f\n", m, f(m));
		}
	}
	
	{
		int l = ly, r = ry;
		while (r - l > 3) {
			int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
			if (f2(m1) < f2(m2))
				l = m1;
			else
				r = m2; 
		}
		my = l;
		err("l = %d, r = %d\n", l, r);
		for (int m = l; m <= r; m++) {
			if (f2(m) > f2(my))
				my = m;
			err("F(%d) = %.10f\n", m, f2(m));
		}
	}
	
	
	
	err("lx = %d, mx = %d, rx = %d\n", lx, mx, rx);
	err("ly = %d, my = %d, ry = %d\n", ly, my, ry);
	
	int X[] = { lx, mx, rx };
	int Y[] = { ly, my, ry };
	
	sort(X, X + 3);
	do {
		sort(Y, Y + 3);
		do {	
			check(X[0], Y[0], X[1], Y[1], X[2], Y[2]);
		} while (next_permutation(Y, Y + 3));
	} while (next_permutation(X, X + 3));
	assert(ok);	
	answer[0][0] = Q[0].first, answer[0][1] = Q[0].second;
	answer[1][0] = Q[1].first, answer[1][1] = Q[1].second;
	answer[2][0] = Q[2].first, answer[2][1] = Q[2].second;
}