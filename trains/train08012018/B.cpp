#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int a[5];

long double ans;
long double ansX;

long double get(long double x) {
	long double p = 1, s = 0;
	for (int i = 0; i < 5; i++) {
		s += a[i] * p;
		p *= x;
	}
	if (s < ans) {
		ans = s;
		ansX = x;
	}
	return s;
}

int main() {
	for (int i = 4; i >= 0; i--) cin >> a[i];
	
	
	ansX = 0;
	ans = get(ansX);
	
	srand(1488);
	
	for (int it1 = 0; it1 < 500; it1++) {
    	long double step = 1e5;
    	long double x = 0;
    	for (int it = 0; it < 5000; it++) {
    		long double nx = (rand() & 1 ? x + step : x - step);
    		if (get(nx) < get(x)) x = nx;
    		step *= 0.99;
    	}
	}
	
	cout.precision(10);
	cout << fixed << (double)ansX << "\n";

	return 0;
}