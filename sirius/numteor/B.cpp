#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int gcd(int a, int b, int c, int &x1, int &y1) {
	if (b == 0) {
		x1 = c / a, y1 = 0;
		return a;
	}
	
	int x2, y2;
	int t = gcd(b, a % b, c, x2, y2);
	
	x1 = y2;
	y1 = x2 - (a / b) * y2;
	
	return t;
}

int main() {
	
	int a, b, c;
	cin >> a >> b >> c;
	
	int t = __gcd(a, b);
	
	if (c % t) return 0 * puts("Impossible");
	
	a /= t, b /= t, c /= t;
	
	int x, y;
	gcd(a, b, c, x, y);
	
	
	int q = __gcd(a, b);
	
	while (x - b / q >= 0) {
		x -= b / q;
		y += a / q;
	}
	
	while (x < 0) {
		x += b / q;
		y -= a / q;
	}
	
	cout << x << " " << y << "\n";
	return 0;
}