#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct stick { int x, y, h; };
struct circle { double x, y, r; };

bool in(circle A, double x, double y) {
	return (x - A.x) * (x - A.x) + (y - A.y) * (y - A.y) <= A.r * A.r;
}

double get(double h, double rad) {
if (h >= rad) {
return rad;
}
double temp = rad - h;
return sqrt(rad * rad - temp * temp);
}

bool notin(double x, double y, vector<circle> &T) {
	for (auto c : T) if (in(c, x, y)) return 0;
	return 1;
}

bool filled(vector<circle> &T, double x1, double y1, double x2, double y2, int depth = 0) {
	for (auto C : T) {
		if (in(C, x1, y1) && in(C, x2, y2) && in(C, x1, y2) && in(C, x2, y1)) return true;
	}
	
	if (notin(x1, y1, T)) return false;
	if (notin(x1, y2, T)) return false;
	if (notin(x2, y1, T)) return false;
	if (notin(x2, y2, T)) return false;
	
	
	if (depth >= 30) {
		return false;
	}
	
	double xm = (x1 + x2) / 2;
	double ym = (y1 + y2) / 2;
	
	if (!filled(T, x1, y1, xm, ym, depth + 1)) return false;
	if (!filled(T, xm, ym, x2, y2, depth + 1)) return false;
	if (!filled(T, x1, ym, xm, y2, depth + 1)) return false;
	if (!filled(T, xm, y1, x2, ym, depth + 1)) return false;
	return true;
}

int main() {
	int n, w;
	while (cin >> n >> w) {
		if (n == 0 && w == 0) break;
		
		vector<stick> A(n);
		for (int i = 0; i < n; i++) cin >> A[i].x >> A[i].y >> A[i].h;
		
		A.push_back({ 0, 0, w });
		A.push_back({ 0, 100, w });
		A.push_back({ 100, 0, w });
		A.push_back({ 100, 100, w });
		
		n += 4;
		
		double l = 0, r = 5000;
		for (int it = 0; it < 44; it++) {
			double m = (l + r) / 2;
			
			vector<circle> T;
			for (int i = 0; i < n; i++) {
				T.push_back({ (double)A[i].x, (double)A[i].y, get(A[i].h, m) });
			}
			
			double x = get(w, m);
			if (x > 100 - x || filled(T, x, x, 100 - x, 100 - x)) r = m;
			else l = m;
		}
		cout.precision(10);
		cout << fixed << l << "\n";
	}
	return 0;
}