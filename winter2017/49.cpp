#include <iostream>
#include <cmath>

using namespace std;

int type(int x, int y) {
	if (x == 0 || y == 0) return -1;
	if (x > 0 && y > 0) return 1;
	if (x < 0 && y > 0) return 2;
	if (x < 0 && y < 0) return 3;
	return 4;
}


int get(int x, int y) {
	return min(abs(x), abs(y));
}

int main() {
	int n;
	cin >> n;
	
	int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
	int mn1 = -1, mn2 = -1, mn3 = -1, mn4 = -1;
	int x1 = -1, y1 = -1, x2 = -1, y2 = -1, x3 = -1, y3 = -1, x4 = -1, y4 = -1;
	
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		
		int tp = type(x, y);
		if (tp == -1) continue;

		if (tp == 1) {
			if (c1 == 0) mn1 = get(x, y), x1 = x, y1 = y;
			else if (mn1 > get(x, y)) mn1 = get(x, y), x1 = x, y1 = y;
			c1++;
		}
		if (tp == 2) {
			if (c2 == 0) mn2 = get(x, y), x2 = x, y2 = y;
			else if (mn2 > get(x, y)) mn2 = get(x, y), x2 = x, y2 = y;
			c2++;
		}
		if (tp == 3) {
			if (c3 == 0) mn3 = get(x, y), x3 = x, y3 = y;
			else if (mn3 > get(x, y)) mn3 = get(x, y), x3 = x, y3 = y;
			c3++;
		}
		if (tp == 4) {
			if (c4 == 0) mn4 = get(x, y), x4 = x, y4 = y;
			else if (mn4 > get(x, y)) mn4 = get(x, y), x4 = x, y4 = y;
			c4++;
		}
	}
	
	int k = 0, m = 0, ax = 0, ay = 0;
	if (c1 >= c2 && c1 >= c3 && c1 >= c4) k = 1, m = c1, ax = x1, ay = y1;
	else if (c2 >= c1 && c2 >= c3 && c2 >= c4) k = 2, m = c2, ax = x2, ay = y2; 
	else if (c3 >= c1 && c3 >= c2 && c3 >= c4) k = 3, m = c3, ax = x3, ay = y3; 
	else k = 4, m = c4, ax = x4, ay = y4; 
	
	cout << "K = " << k << "\n";
	cout << "M = " << m << "\n";
	cout << "A = " << "(" << ax << ", " << ay << ")\n";
	cout << "R = " << get(ax, ay) << "\n";
	
	return 0;
}