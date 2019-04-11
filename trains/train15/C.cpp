#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

double dist(double x1, double y1, double x2, double y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main() {
	double l, x, y, r, v, t;
	cin >> l >> x >> y >> r >> v >> t;

	double R = sqrt(x * x + y * y);
	double Vx = -x / R * v;
	double Vy = -y / R * v;

	double tt = R / v;
	double t2 = r / v;

	double ans = 1e18;

	while (tt > 0) {
		double cur = min(dist(x, y, l, 0), dist(x, y, -l, 0));
		ans = min(ans, cur / min(t2, tt));
		err("cur = %.3f\n, tm = %.3f\n", cur, min(t2, tt));
		tt -= t;
		x += Vx * t, y += Vy * t;
	}
	printf("%.10f", ans);
	return 0;
}